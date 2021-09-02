//utility functions used to convert things for display and sending over radio

#ifndef UTILS_H
#define	UTILS_H

#include <xc.h>
#include <math.h>

//convert an unsigned integer to a character (num < 10)
static inline char DigitToChar(uint8_t num)
{
    return num + '0';
}

//return a specific digit of a number (pos = 0 is the least significant digit)
static inline uint8_t GetDigit(float number, uint8_t pos)
{
    number = number >= 0.0 ? number : -number;
    
    return ((int)number / (int)pow(10, pos)) % 10;
}

//convert the measured distance to a str for display on the LCD
void DistanceToStr(uint16_t distance, char* out_str);

//convert the measured temperature to a str for display on the LCD
void TemperatureToStr(int8_t temperature, char* out_str);

//calculate the distance (in mm) from the echo return time (in us), and the temperature (in Celsius)
uint16_t CalcDistance(uint16_t bounce_time_us, float temperature_c);


#endif	/* UTILS_H */