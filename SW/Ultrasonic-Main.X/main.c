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
    SYSTEM = 0,
    SINGLE = 1
} DEVICE_MODE;
DEVICE_MODE device_mode = SYSTEM;  //currently unused

//radio state
RF_MODE radio_mode;
#define PACKET_SIZE 3

//EEPROM
uint16_t eeprom_address;

//USB read and write buffers
struct USB_BUFFERS usb_buffers;

//flags
volatile bool SEND_ECHO = true;
volatile bool ECHO_RET = false;
volatile bool MSG_SENT = false;
volatile bool MSG_RECEIVED = false;
volatile bool MEAS_PRESS = false;

volatile uint16_t echo_time = 0;    //echo travel time in us (both ways)

void Init(void);
void IO_InterruptHandler(void); //handles all IO pin interrupts
void T1_InterruptHandler(void); //handles the periodic measurements


int main(void)
{
    Init();
    
    int8_t temperature_main = (int8_t)T_ReadTemperature();  //temperature measured by the main unit (in Celsius)
    int8_t temperature_extern = temperature_main;           //temperature measured by the distant unit (in Celsius)
    
    while (1)
    {
        if (SEND_ECHO)
        {
            SEND_ECHO = false;
            TMR1_Counter16BitSet(0);
            
            //send a trigger pulse to the ultrasonic distance sensor to begin measurement
            
            TRIG_SetHigh();
            __delay_us(10);
            TRIG_SetLow();
        }
        
        if (ECHO_RET && echo_time < 40000)
        {
            ECHO_RET = false;
            
            //the echo return signal was detected by the ultrasonic distance sensor and the measurement is done
            //send the results of the measurement (echo time, and temperature) to the extern unit
            //the results of the measurement are not displayed on this unit yet, only after a response from
            //the extern unit was received (with the temperature measured by that unit)
            //both temperature values are used to calculate to distance from the echo return time
            
            //switch the radio to transmit mode and write the packet to be sent to the transmit FIFO
            //the packet consists of the high and low bytes of the echo time and the temperature byte
            radio_mode = MODE_TX;
            RF_SetMode(MODE_TX);
            RF_SetFIFOThreshold(PACKET_SIZE - 2);
            
            //echo time
            RF_WriteTransmitFIFO(echo_time >> 8);  //high
            RF_WriteTransmitFIFO(echo_time);       //low
            //temperature
            temperature_main = (int8_t)T_ReadTemperature();
            RF_WriteTransmitFIFO(ConvertI8toU8(temperature_main));
        }
        if (MSG_SENT)
        {
            MSG_SENT = false;
            
            //the packet containing the measurement results was sent out by the RF module
            //switch the radio to receiver mode and wait for the answer by the extern module
            
            RF_SetMode(radio_mode = MODE_RX);
            //set the interrupt threshold for receiver mode
            RF_SetFIFOThreshold(PACKET_SIZE - 1);
        }
        if (MSG_RECEIVED)
        {
            MSG_RECEIVED = false;
            
            //the response packet was received from the extern unit and is in the RF module receive FIFO
            //the packet contains 2 cmd bytes and a temperature byte measured by the extern unit's temperature sensor
            //calculate the distance using this information and update the LCD display with the new results
            //(also handle the EEPROM if needed)
            
            LED_MODE_Toggle();
            
            uint8_t cmd_byte_high = RF_ReadReceiveFIFO();  //unused
            uint8_t cmd_byte_low = RF_ReadReceiveFIFO();   //unused
            uint8_t temperature_byte = RF_ReadReceiveFIFO();
            
            //calculate temperature
            temperature_extern = ConvertU8toI8(temperature_byte);
            //calculate the distance (from the 2-way echo return time) in mm (min 2cm, max 4m) and the temperature
            //only the main unit's temperature readings are used currently, because
            //of the inaccuracy of the extern unit's temperature sensor, but the average of the 2 temperatures
            //should be used if it's more accurate
            uint16_t distance = CalcDistance(echo_time, (float)temperature_main);

            //write result to the EEPROM (16bit distance in mm)
            //only every other distanc measurement is saved
            static bool save_dist = 0;
            if (save_dist++)
            {
                //EEPROM_Write16bits(eeprom_address, distance);
            }
            
            //display results on LCD (distance and temperature)
            char line1[7], line2[5];
            DistanceToStr(distance, line1);
            TemperatureToStr(temperature_main, line2);
            LCD_WriteStrFrom(LCD_LINE1, 7, line1, sizeof(line1));
            LCD_WriteStrFrom(LCD_LINE2, 7, line2, sizeof(line2));
            
            //switch the radio to standby mode until the next measurement
            RF_SetMode(radio_mode = MODE_STANDBY);
        }
        if (MEAS_PRESS)
        {
            MEAS_PRESS = false;
            
            //the MEAS button was pressed, unused
        }
        
        //handle USB communication if necessary
        USB_Transfer(&usb_buffers);
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
    
    //initialize the EEPROM
    eeprom_address = EEPROM_Initialize();
    
    //set the interrupt handlers
    CN_SetInterruptHandler(IO_InterruptHandler);
    TMR1_SetInterruptHandler(T1_InterruptHandler);
}

void IO_InterruptHandler(void)
{
    //read ports and determine what triggered the interrupt
    uint16_t porta = PORTA;
    uint16_t portb = PORTB;
    
    static bool echo_old = 0;
    static bool radio0_old = 0;
    static bool radio1_old = 0;
    static bool button_old = 0;
    
    bool echo = porta & 16;
    bool radio0 = porta & 1;
    bool radio1 = portb & 4;
    bool button = portb & 128;
    
    bool echo_change = echo_old ^ echo;
    bool radio0_change = radio0_old ^ radio0;
    bool radio1_change = radio1_old ^ radio1;
    bool button_change = button_old ^ button;
    
    
    //echo signal interrupt (on rising edge)
    if (echo_change && echo)
    {
        ECHO_RET = true;
        
        //the returning echo was detected by the distance sensor
        //measure the return time
        
        //distance measurement offset error correction (in us)
        //calculated based on measurements, so the mean error will be ~ 0 mm
        TMR2 = 58;
        
        //distance ~ ECHO_HIGH time
        //we wait until the echo pin goes low here
        //(we know the radio interrupts can't trigger until after the measurements,
        //and the measure button interrupt can be ignored if there is a measurement in progress already)
        //waiting here will result in a more accurate measurement
        while (ECHO_GetValue());
        echo_time = TMR2;        //time in us
    }
    
    //transmit mode radio interrupts
    if (radio_mode == MODE_TX)
    {
        //FIFO = FIFO_THRESHOLD reached interrupt (packet ready to transmit) (on falling edge)
        if (radio0_change && !radio0)
        {
            //this interrupt is unused
        }
        //TX DONE interrupt (transmission complete) (on rising edge)
        if (radio1_change && radio1)
        {
            MSG_SENT = true;
        }
    }
    //receiver mode radio interrupts
    else if (radio_mode == MODE_RX)
    {
        //SYNC or ADDRESS match interrupt (packet incoming) (on rising edge)
        if (radio0_change && radio0)
        {
            //this interrupt is unused
        }
        //FIFO = FIFO_THRESHOLD reached interrupt (full packet received) (on rising edge)
        if (radio1_change && radio1)
        {
            MSG_RECEIVED = true;
        }
    }
    //measure button interrupt (on rising edge)
    if (button_change && button && device_mode == SINGLE)
    {
        __delay_ms(15); //debounce delay
        
        if (MEAS_GetValue())
        {
            MEAS_PRESS = true;
        }
    }
    
    //read ports again    
    echo_old = PORTA & 16;
    radio0_old = PORTA & 1;
    radio1_old = PORTB & 4;
    button_old = PORTB & 128;
}

void T1_InterruptHandler(void)
{
    //start a new measurement cycle
    SEND_ECHO = true;
}