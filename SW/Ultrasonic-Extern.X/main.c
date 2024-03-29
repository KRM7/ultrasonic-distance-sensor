//Distant/extern unit

#include "mcc_generated_files/mcc.h"
#include "radio.h"
#include "io_utils.h"
#include "temperature.h"
#include "7segment.h"
#include <math.h>

//for the delays
#include "mcc_generated_files/clock.h"
#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"

typedef enum {
    MODE_SYSTEM = 0,
    MODE_SINGLE = 1
} DeviceMode;
DeviceMode dev_mode = MODE_SYSTEM; //currently unused

//7-segment display state
struct SevenSegment display;

//radio state
RF_MODE radio_mode;
#define PACKET_SIZE 3

//flags
volatile bool MSG_RECEIVED = false;
volatile bool MSG_SENT = false;
volatile bool MODE_PRESS = false;

void Init(void);
void IO_InterruptHandler(void); //IO interrupt handler (this handles every IO pin interrupt)
void T1_InterruptHandler(void); //handles the 7 segment display


int main(void)
{
    Init();

    uint16_t distance = 0; //measured distance in mm (min 2cm, max 4m)
    int8_t temperature_extern = (int8_t) T_ReadTemperature(); //in Celsius
    int8_t temperature_main = temperature_extern; //in Celsius

    while (1)
    {
        if (MSG_RECEIVED)
        {
            MSG_RECEIVED = false;

            //a packet was received from the main unit, and is in the RF module's receive FIFO
            //the packet contains in order: echo time high and low bytes, temperature byte measured by the main units sensor
            //update the 7 segment display based on the new data received from the main unit
            //send back an answer with the temperature measured by this unit

            //get the received packet from the RF module's receive FIFO
            uint8_t echo_time_high = RF_ReadReceiveFIFO();
            uint8_t echo_time_low = RF_ReadReceiveFIFO();
            uint8_t temp_byte = RF_ReadReceiveFIFO();

            //read/measure the temperature values measured by the two units
            temperature_main = ConvertU8toI8(temp_byte);
            temperature_extern = (int8_t) T_ReadTemperature();

            //calculate the distance from the echo time
            //only use the main units temperature measurement in the calculation because of the inaccuracy
            //of the extern units temperature measurements
            //the average of the main and extern temperatures should be used if it is more accurate
            uint16_t echo_time = ((uint16_t) echo_time_high << 8) | (uint16_t) echo_time_low; //two-way time in us
            distance = CalcDistance(echo_time, (float) temperature_main);

            //display the distance in cm on the 7segment display
            SSEG_SetDisplayValue(&display, distance / 10); //mm->cm


            //send answer message to the main unit containing the temperature measured by this unit
            RF_SetMode(radio_mode = MODE_TX);
            //update the interrupt/transmit start threshold for transmit mode
            RF_SetFIFOThreshold(PACKET_SIZE - 2);

            RF_WriteTransmitFIFO(0x00); //cmd byte0, unused
            RF_WriteTransmitFIFO(0x00); //cmd byte1, unused
            RF_WriteTransmitFIFO(ConvertI8toU8(temperature_extern)); //temperature byte           
        }

        if (MSG_SENT)
        {
            MSG_SENT = false;

            //the answer has been sent out to the main unit
            //switch back this unit's RF module to receiver mode

            RF_SetMode(radio_mode = MODE_RX);
            //update the interrupt threshold for receiver mode
            RF_SetFIFOThreshold(PACKET_SIZE - 1);

            LED_MODE_Toggle();
        }

        if (MODE_PRESS)
        {
            MODE_PRESS = false;

            //the mode button was pressed, unused
        }

        //update the warning LEDs based on the distance
        distance < 250 ? LED_WARN1_SetHigh() : LED_WARN1_SetLow(); // < 25cm
        distance < 500 ? LED_WARN2_SetHigh() : LED_WARN2_SetLow(); // < 50cm
    }

    return 1;
}

void Init(void)
{
    //initialize the microcontroller
    __delay_ms(10);
    SYSTEM_Initialize();

    //initialize the RF module
    RF_Initialize();
    RF_SetMode(radio_mode = MODE_RX);
    RF_SetFIFOThreshold(PACKET_SIZE - 1);
    RF_SetPacketSize(PACKET_SIZE);

    //initialize the 7segment display
    SSEG_Init(&display);

    //set interrupt handlers
    CN_SetInterruptHandler(IO_InterruptHandler);
    TMR1_SetInterruptHandler(T1_InterruptHandler);
}

void IO_InterruptHandler(void)
{
    //read input ports and determine what triggered the interrupt
    uint16_t porta = PORTA;
    uint16_t portb = PORTB;

    static bool radio0_old = 0;
    static bool radio1_old = 0;
    static bool button_old = 0;

    bool radio0 = portb & 16; //RB14
    bool radio1 = portb & 8;  //RB3
    bool button = porta & 4;  //RA2

    bool radio0_changed = radio0_old ^ radio0;
    bool radio1_changed = radio1_old ^ radio1;
    bool button_changed = button_old ^ button;


    //transmit mode radio interrupts
    if (radio_mode == MODE_TX)
    {
        //FIFO = FIFO_THRESHOLD reached interrupt (packet ready to transmit) (on falling edge)
        if (radio0_changed && !radio0)
        {
            //this interrupt is unused
        }
        //TX DONE interrupt (transmission complete) (on rising edge)
        if (radio1_changed && radio1)
        {
            MSG_SENT = true;
        }
    }
    //receiver mode radio interrupts
    else if (radio_mode == MODE_RX)
    {
        //SYNC or ADDRESS match interrupt (packet incoming) (on rising edge)
        if (radio0_changed && radio0)
        {
            //this interrupt is unused
        }
        //FIFO = FIFO_THRESHOLD reached interrupt (full packet received) (on rising edge)
        if (radio1_changed && radio1)
        {
            MSG_RECEIVED = true;
        }
    }
    //MODE button pressed interrupt (on rising edge)
    if (button_changed && button)
    {
        __delay_ms(15); //debounce delay for the button        
        if (SW_MODE_GetValue())
        {
            MODE_PRESS = true;
        }
    }

    //read ports again   
    radio0_old = PORTB & 16; //RB14
    radio1_old = PORTB & 8;  //RB3
    button_old = PORTA & 4;  //RA2
}

void T1_InterruptHandler(void)
{
    //move the "cursor" to the next digit/position and display the value in that position on the 7segment display
    SSEG_NextPos(&display);
    SSEG_DisplayDigit(&display);
}