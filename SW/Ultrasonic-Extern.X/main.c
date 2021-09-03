//Distant/extern unit

#include "mcc_generated_files/mcc.h"
#include "radio.h"
#include "io_utils.h"
#include "temperature.h"
#include <math.h>

//for the delays
#include "mcc_generated_files/clock.h"
#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"

//device mode
//typedef enum{
//    SYSTEM = 0b0,
//    SINGLE = 0b1
//} DEVICE_MODE;
//volatile DEVICE_MODE MODE = SYSTEM;

//7 segment display
int current_display_pos = 2;
#define incrementDisplayPos() (current_display_pos = (current_display_pos + 1) % 3)
uint16_t DISPLAY_VALUE = 123;
#define DIGIT1 ((int)(DISPLAY_VALUE/100) % 10)
#define DIGIT2 ((int)(DISPLAY_VALUE/10) % 10)
#define DIGIT3 (DISPLAY_VALUE % 10)

//measurement data
volatile uint16_t distance = 0;         //measured distance in mm (min 2cm, max 4m)
volatile uint16_t echo_time = 0;        //echo travel time in us (both ways)
volatile int8_t temperature_main = 0;    //temperature measured by the main unit (in Celsius)
volatile int8_t temperature_extern = 0;  //temperature measured by the distant unit (in Celsius)

//radio mode
volatile RF_MODE radio_mode;
#define PACKET_SIZE 4

//functions
void Init(void);
void IO_InterruptHandler(void);
void T1_InterruptHandler(void);
void displayClockPulse(void);
void displayDigit(int digit);

int main(void)
{
    Init();

    while (1)
    {
        if (radio_mode == MODE_STANDBY)
        {
            RF_SetMode(radio_mode = MODE_TX);
            RF_SetFIFOThreshold(PACKET_SIZE - 2);
            
            RF_WriteTransmitFIFO(0x00);     //cmd byte0
            RF_WriteTransmitFIFO(0x00);     //cmd byte1                 
            RF_WriteTransmitFIFO(ConvertI8toU8(temperature_extern));    //temperature byte0
            RF_WriteTransmitFIFO(ConvertI8toU8(temperature_extern));    //temperature byte1
        }
        
        distance < 250 ? LED_WARN1_SetHigh() : LED_WARN1_SetLow();
        distance < 500 ? LED_WARN2_SetHigh() : LED_WARN2_SetLow();
    }

    return 1;
}

void Init(void)
{
    //initialize the device
    __delay_ms(10);
    SYSTEM_Initialize();
    RF_Initialize();
    
    //initialize the RF module
    RF_SetMode(radio_mode = MODE_RX);
    RF_SetFIFOThreshold(PACKET_SIZE - 1);
    RF_SetPacketSize(PACKET_SIZE);
    
    //initialize the temperatures
    temperature_main = (int8_t)T_ReadTemperature();
    temperature_extern = temperature_main;
    
    CN_SetInterruptHandler(IO_InterruptHandler);
    TMR1_SetInterruptHandler(T1_InterruptHandler);
}

void IO_InterruptHandler(void)
{  
    uint16_t porta = PORTA;
    uint16_t portb = PORTB;
    
    bool RF0 = portb & 16;  //RB14
    bool RF1 = portb & 8;   //RB3
    bool SW = porta & 4;    //RA2
    
    //transmit mode radio interrupts
    if (radio_mode == MODE_TX)
    {
        //FIFO >= FIFO_THRESHOLD interrupt (transmit start)
        if (RF0) {}
        //TX DONE interrupt
        if (RF1)
        {
            //switch back to receive mode
            RF_SetMode(radio_mode = MODE_RX);
            RF_SetFIFOThreshold(PACKET_SIZE - 1);
            LED_MODE_Toggle();
        }
    }
    //receiver mode radio interrupts
    else if (radio_mode == MODE_RX)
    {
        //SYNC or ADDRESS match interrupt
        if (RF0) {}
        //FIFO > FIFO_THRESHOLD interrupt (packet received)
        if (RF1)
        {
            uint8_t echo_time_high = RF_ReadReceiveFIFO();
            uint8_t echo_time_low = RF_ReadReceiveFIFO();
            uint8_t temp_high = RF_ReadReceiveFIFO();
            uint8_t temp_low = RF_ReadReceiveFIFO();
            
            //calculate temperature
            temperature_main = ConvertU8toI8(temp_high);
            temperature_extern = (int8_t)T_ReadTemperature();
            
            //calculate and display distance in cm
            echo_time = ((uint16_t)echo_time_high << 8) | (uint16_t)echo_time_low;  //time in us
            distance = CalcDistance(echo_time, (float)temperature_main);
            
            //display distance in cm
            DISPLAY_VALUE = distance / 10;
            
            RF_SetMode(radio_mode = MODE_STANDBY);
        }
    }
    
    //MODE button pressed
//    else if (SW)
//    {
//        //debounce delay
//        __delay_ms(15);
//        if (SW_MODE_GetValue())
//        {
//        }
//    }
}

//handles the 7 segment display
void T1_InterruptHandler(void)
{
    incrementDisplayPos(); //0-2 cycle
    displayClockPulse();
    switch (current_display_pos)
    {
        case 0:
            displayDigit(DIGIT1);
            break;
        case 1:
            displayDigit(DIGIT2);
            break;
        case 2:
            displayDigit(DIGIT3);
            break;
        default:
            break;
    }
}

//increments decade counter by 1 //switches digits on 7 segment
void displayClockPulse(void)
{  
    CNTR_CLK_SetHigh();
    __delay_us(2);      //min 0.3 us
    CNTR_CLK_SetLow();
}

//displays 1 digit on the 7 segment display
void displayDigit(int digit)
{
    _LATB7 = (digit & ( 1 << 0 )) >> 0;     //LED_A
    _LATB8 = (digit & ( 1 << 1 )) >> 1;     //LED_B
    _LATB9 = (digit & ( 1 << 2 )) >> 2;     //LED_C
    _LATB6 = (digit & ( 1 << 3 )) >> 3;     //LED_D
}