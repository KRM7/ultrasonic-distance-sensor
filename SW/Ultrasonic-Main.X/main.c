//Main device

#include "mcc_generated_files/mcc.h"

#include "i2c.h"
#include "temperature.h"
#include "radio.h"
#include "lcd.h"
#include "io_utils.h"
#include "eeprom.h"
#include "usb.h"

#include <math.h>

//for the delays
#include "mcc_generated_files/clock.h"
#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"

//device modes
typedef enum {
    SYSTEM = 0b0,
    SINGLE = 0b1
} DEVICE_MODE;
volatile DEVICE_MODE device_mode = SYSTEM;

//measurement data
volatile bool signal_sent = false;
volatile float distance = 0.0;              //measured distance in mm (min 2cm, max 4m)
volatile uint16_t echo_time = 0;            //echo travel time in us (both ways)
volatile float temperature_main = 0.0;      //temperature measured by the main unit (in Celsius)
volatile float temperature_extern = 0.0;    //temperature measured by the distant unit (in Celsius)

//radio
volatile RF_MODE radio_mode = MODE_TX;
#define PACKET_SIZE 4

//EEPROM
volatile uint16_t eeprom_address;

//USB
struct USB_BUFFERS usb_buffers;

void Init(void);
void IO_InterruptHandler(void);
void TriggerPulse(void);

int main(void)
{
    Init();

    while (1)
    {     
        //send trigger
        signal_sent = false;
        TriggerPulse();
        __delay_ms(60);
        
        if (signal_sent && echo_time < 40000)
        {
            //transmit mode
            radio_mode = MODE_TX;
            RF_SetMode(MODE_TX);
            RF_SetFIFOThreshold(PACKET_SIZE - 2);
            
            //send time
            RF_WriteTransmitFIFO(echo_time >> 8);
            RF_WriteTransmitFIFO(echo_time);
            
            //send temperature
            int16_t temp = (int16_t)((temperature_main + 40) * 10); //(T+40)*10 in int
            uint16_t tempu = (uint16_t)temp;
            RF_WriteTransmitFIFO(tempu >> 8);
            RF_WriteTransmitFIFO(tempu);

            USB_Transfer(&usb_buffers);
            __delay_ms(450);
        }
     
    }

    return 1;
}

void Init(void)
{
    //initialize the device
    __delay_ms(10);
    SYSTEM_Initialize();
    I2C_Init();
    TMR2_Start();
        
    //initialize the RF module
    RF_Initialize();
    RF_SetMode(radio_mode = MODE_STANDBY);
    RF_SetFIFOThreshold(4);
    RF_SetPacketSize(4);
    
    //initialize the LCD
    LCD_Initialize();
    const char* line1 = "Dist: ";
    LCD_WriteStrFrom(LCD_LINE1, 1, line1, sizeof(line1));
    const char* line2 = "Temp: ";
    LCD_WriteStrFrom(LCD_LINE2, 1, line2, sizeof(line2));
    
    //initialize the temperature values
    temperature_main = T_ReadTemperature();
    temperature_extern = temperature_main;
    
    //initialize the EEPROM
    eeprom_address = EEPROM_Initialize();
    
    CN_SetInterruptHandler(IO_InterruptHandler);
}

void IO_InterruptHandler(void){ //ultrasonic sensor, radio, button interrupts are handled here
    
    uint16_t porta = PORTA;
    uint16_t portb = PORTB;
    
    bool ECHO = porta & 16;
    bool RF0 = porta & 1;
    bool RF1 = portb & 4;
    bool MEAS = portb & 128;
    
    //echo signal interrupt
    if (ECHO)
    {
        TMR2 = 58; //offset error correction
        
        while (ECHO_GetValue()); //distance~ECHO_HIGH
        
        echo_time = TMR2; //time in us
        temperature_main = T_ReadTemperature();
        signal_sent = true;
    }
    
    //transmit mode radio interrupts
    else if (radio_mode == MODE_TX)
    {
        //FIFO >= FIFO_THRESHOLD interrupt (packet ready)
        if (RF0)
        {
        }
        //TX DONE interrupt (radio transmission complete)
        if (RF1)
        {
            //switch the radio to receiver mode
            RF_SetMode(radio_mode = MODE_RX);
            RF_SetFIFOThreshold(PACKET_SIZE - 1);
        }
    }
    //receiver mode radio interrupts
    else if (radio_mode == MODE_RX)
    {
        //SYNC or ADDRESS match interrupt
        if (RF0)
        {
        }
        //FIFO > FIFO_THRESHOLD interrupt (packet received)
        if (RF1)
        {
            //read the answer
            LED_MODE_Toggle();
            
            uint8_t cmd_byte1 = RF_ReadReceiveFIFO();
            uint8_t cmd_byte0 = RF_ReadReceiveFIFO();
            uint8_t temperature_byte1 = RF_ReadReceiveFIFO();
            uint8_t temperature_byte0 = RF_ReadReceiveFIFO();
            
            //calculate temperature
            uint16_t tempu = ((uint16_t)temperature_byte1 << 8) | (uint16_t)temperature_byte0; //(T+40)*10 in uint
            int16_t temp = (int16_t)tempu;
            temperature_extern = (float)temp/10.0 - 40.0; //TEMP in C
            
            //calculate distance in mm
            distance = CalcDistance((float)echo_time, temperature_main);

            //write result to the EEPROM (16bit distance in mm) every 1 sec
            static bool b = 0;
            if (b++)
            {
                EEPROM_Write16bits(eeprom_address, (uint16_t)distance);
            }
            
            //display results on LCD
            char line1[7], line2[5];
            DistanceToStr(distance, line1);
            TemperatureToStr(temperature_main, line2);
            LCD_WriteStrFrom(LCD_LINE1, 7, line1, sizeof(line1));
            LCD_WriteStrFrom(LCD_LINE2, 7, line2, sizeof(line2));
            
            //standby mode until next measurement
            RF_SetMode(radio_mode = MODE_STANDBY);   
        }
    }
     
//    else if (MEAS && device_mode == SINGLE)
//    {
//        __delay_ms(15);         //debounce delay
//        if (MEAS_GetValue())
//        {
//            //TriggerPulse();     //send trigger pulse
//            //TMR2 = 0;           //timer start
//        }
//    }
}

void TriggerPulse(void)
{
    TRIG_SetHigh();
    __delay_us(10);
    TRIG_SetLow();
}

/*END OF FILE*/