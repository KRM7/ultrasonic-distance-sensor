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

//calculate the distance (in mm) from the echo return time (in us), and the temperature (in Celsius)
uint16_t CalcDistance(uint16_t bounce_time_us, float temperature_c);

//reinterpret int8 as uint8
static inline uint8_t convertI8toU8(int8_t i8)
{
    return *(uint8_t*)&i8;
}

//reinterpret uint8 as int8
static inline int8_t convertU8toI8(uint8_t u8)
{
    return *(int8_t*)&u8;
}

//reinterpret int16 as uint16
static inline uint16_t convertI16toU16(int16_t i16)
{
    return *(uint16_t*)&i16;
}

//reinterpret uint16 as int16
static inline int16_t convertU16toI16(uint16_t u16)
{
    return *(int16_t*)&u16;
}

#endif	/* UTILS_H */