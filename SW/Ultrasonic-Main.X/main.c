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


typedef enum {
    SYSTEM = 0b0,
    SINGLE = 0b1
} DEVICE_MODE;
volatile DEVICE_MODE device_mode = SYSTEM;

//measurement data
volatile bool signal_sent = false;
volatile uint16_t distance = 0;             //measured distance in mm (min 2cm, max 4m)
volatile uint16_t echo_time = 0;            //echo travel time in us (both ways)
volatile int8_t temperature_main = 0;       //temperature measured by the main unit (in Celsius)
volatile int8_t temperature_extern = 0;     //temperature measured by the distant unit (in Celsius)

//radio
volatile RF_MODE radio_mode;
#define PACKET_SIZE 3

//EEPROM
volatile uint16_t eeprom_address;

//USB
struct USB_BUFFERS usb_buffers;

//flags
volatile bool MSG_SENT = false;
volatile bool MSG_RECEIVED = false;
volatile bool MEAS_PRESS = false;
volatile bool ECHO_RET = false;

void Init(void);
void IO_InterruptHandler(void); //handles all IO interrupts
void TriggerPulse(void);

int main(void)
{
    Init();

    while (1)
    {     
        TriggerPulse();
        __delay_ms(60);
        
        if (ECHO_RET && echo_time < 40000)
        {
            //transmit mode
            radio_mode = MODE_TX;
            RF_SetMode(MODE_TX);
            RF_SetFIFOThreshold(PACKET_SIZE - 2);
            
            //send time
            RF_WriteTransmitFIFO(echo_time >> 8);
            RF_WriteTransmitFIFO(echo_time);
            
            //send temperature
            RF_WriteTransmitFIFO(ConvertI8toU8(temperature_main));

            USB_Transfer(&usb_buffers);
            __delay_ms(450);
        }
        if (MSG_SENT)
        {
            MSG_SENT = false;
            
            
        }
        if (MSG_RECEIVED)
        {
            MSG_RECEIVED = false;
            
            
        }
        if (MEAS_PRESS)
        {
            MEAS_PRESS = false;
            
            
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
    RF_SetFIFOThreshold(PACKET_SIZE);
    RF_SetPacketSize(PACKET_SIZE);
    
    //initialize the LCD
    LCD_Initialize();
    char line1[6] = "Dist: ";
    LCD_WriteStrFrom(LCD_LINE1, 1, line1, sizeof(line1));
    char line2[6] = "Temp: ";
    LCD_WriteStrFrom(LCD_LINE2, 1, line2, sizeof(line2));
    
    //initialize the temperature values
    temperature_main = (int8_t)T_ReadTemperature();
    temperature_extern = temperature_main;
    
    //initialize the EEPROM
    eeprom_address = EEPROM_Initialize();
    
    //set up the interrupt handlers
    CN_SetInterruptHandler(IO_InterruptHandler);
}

void IO_InterruptHandler(void)
{
    //read ports
    uint16_t porta = PORTA;
    uint16_t portb = PORTB;
    
    static bool ECHO_OLD = 0;
    static bool RF0_OLD = 0;
    static bool RF1_OLD = 0;
    static bool MEAS_OLD = 0;
    
    bool ECHO = porta & 16;
    bool RF0 = porta & 1;
    bool RF1 = portb & 4;
    bool MEAS = portb & 128;
    
    bool ECHO_CHANGE = ECHO_OLD ^ ECHO;
    bool RF0_CHANGE = RF0_OLD ^ RF0;
    bool RF1_CHANGE = RF1_OLD ^ RF1;
    bool MEAS_CHANGE = MEAS_OLD ^ MEAS;
    
    ECHO_OLD = ECHO;
    RF0_OLD = RF0;
    RF1_OLD = RF1;
    MEAS_OLD = MEAS;
    
    //echo signal interrupt _/??
    if (ECHO_CHANGE && ECHO)
    {
        TMR2 = 58; //offset error correction
        
        while (ECHO_GetValue()); //distance~ECHO_HIGH
        
        echo_time = TMR2; //time in us
        
        temperature_main = (int8_t)T_ReadTemperature();
        
        ECHO_RET = true;
    }
    
    //transmit mode radio interrupts
    if (radio_mode == MODE_TX)
    {
        //FIFO = FIFO_THRESHOLD reached interrupt (packet ready to transmit) ??\_
        if (RF0_CHANGE && !RF0)
        {
            //this interrupt is unused
        }
        //TX DONE interrupt (transmission complete) _/??
        if (RF1_CHANGE && RF1)
        {
            MSG_SENT = true;
            
            //switch the radio to receiver mode
            RF_SetMode(radio_mode = MODE_RX);
            RF_SetFIFOThreshold(PACKET_SIZE - 1);
        }
    }
    //receiver mode radio interrupts
    else if (radio_mode == MODE_RX)
    {
        //SYNC or ADDRESS match interrupt (packet incoming) _/??
        if (RF0_CHANGE && RF0)
        {
            //this interrupt is unused
        }
        //FIFO = FIFO_THRESHOLD reached interrupt (full packet received) _/??
        if (RF1_CHANGE && RF1)
        {
            MSG_RECEIVED = true;
            //read the answer
            LED_MODE_Toggle();
            
            uint8_t cmd_byte1 = RF_ReadReceiveFIFO();
            uint8_t cmd_byte0 = RF_ReadReceiveFIFO();
            uint8_t temperature_byte = RF_ReadReceiveFIFO();
            
            //calculate temperature
            temperature_extern = ConvertU8toI8(temperature_byte);
            
            //calculate distance in mm
            distance = CalcDistance(echo_time, (float)temperature_main);

            //write result to the EEPROM (16bit distance in mm) every 1 sec
            static bool b = 0;
            if (b++)
            {
                //EEPROM_Write16bits(eeprom_address, distance);
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
    //measure button interrupt _/??
    if (MEAS_CHANGE && MEAS && device_mode == SINGLE)
    {
        __delay_ms(15); //debounce delay
        
        if (MEAS_GetValue())
        {
            MEAS_PRESS = true;
        }
    }
}

void TriggerPulse(void)
{
    TRIG_SetHigh();
    __delay_us(10);
    TRIG_SetLow();
}