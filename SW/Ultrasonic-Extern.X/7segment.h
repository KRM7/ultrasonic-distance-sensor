//Functions for handling the 3 digit 7 segment display

#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H

#include <xc.h>

struct SevenSegment {
    uint16_t current_display_pos;
    uint16_t display_value;
    uint16_t digits[3];     //index 0 is the most significant digit
};

//set the default values for the seven segment display
void SSEG_Init(struct SevenSegment* display);

//move to the next display position
void SSEG_NextPos(struct SevenSegment* display);

//set the displayed value of the seven segment display
void SSEG_SetDisplayValue(struct SevenSegment* display, uint16_t value);

//displays a digit on the 7 segment display
void SSEG_DisplayDigit(struct SevenSegment* display);


#endif	/* SEVEN_SEGMENT_H */