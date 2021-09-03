#include "7segment.h"
#include "xc.h"
#include "io_utils.h"
#include "mcc_generated_files/pin_manager.h"

//for the delays
#include "mcc_generated_files/clock.h"
#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"


void SSEG_Init(struct SevenSegment* display)
{
    display->current_display_pos = 0;
    display->display_value = 123;
    display->digits[0] = 1;
    display->digits[1] = 2;
    display->digits[2] = 3;
}

void SSEG_NextPos(struct SevenSegment* display)
{
    //there are only 3 digits
    display->current_display_pos = (display->current_display_pos + 1) % 3;
    
    //increment display counter
    CNTR_CLK_SetHigh();
    __delay_us(2);      //min 0.3 us
    CNTR_CLK_SetLow();
}

void SSEG_SetDisplayValue(struct SevenSegment* display, uint16_t value)
{
    display->display_value = value;
    
    //update the individual digits
    display->digits[0] = GetDigit((float)value, 2); //most significant digit
    display->digits[1] = GetDigit((float)value, 1);
    display->digits[2] = GetDigit((float)value, 0); //least significant digit
}

void SSEG_DisplayDigit(struct SevenSegment* display)
{
    uint16_t digit = display->digits[display->current_display_pos];
    
    _LATB7 = (digit & ( 1 << 0 )) >> 0;     //LED_A
    _LATB8 = (digit & ( 1 << 1 )) >> 1;     //LED_B
    _LATB9 = (digit & ( 1 << 2 )) >> 2;     //LED_C
    _LATB6 = (digit & ( 1 << 3 )) >> 3;     //LED_D
}