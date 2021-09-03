#include "io_utils.h"
#include "xc.h"
#include <math.h>


void DistanceToStr(uint16_t distance, char* out_str)
{
    //the distance is always positive and 4 digits at most
    float d = (float)distance;
    
    out_str[0] = d >= 1000.0 ? DigitToChar(GetDigit(d, 3)) : ' ';
    out_str[1] = d >= 100.0 ? DigitToChar(GetDigit(d, 2)) : ' ';
    out_str[2] = d >= 10.0 ? DigitToChar(GetDigit(d, 1)) : ' ';
    out_str[3] = DigitToChar(GetDigit(d, 0));
    out_str[4] = ' ';
    out_str[5] = 'm';
    out_str[6] = 'm';
}

void TemperatureToStr(int8_t temperature, char* out_str)
{
    //the temperature can be negative and is at most 2 digits
    float T = (float)temperature;
    
    out_str[0] = T < 0.0 ? '-' : ' ';
    out_str[1] = T > 10.0 ? DigitToChar(GetDigit(T, 1)) : ' ';
    out_str[2] = DigitToChar(GetDigit(T, 0));
    out_str[3] = ' ';
    out_str[4] = 'C';
}

uint16_t CalcDistance(uint16_t bounce_time_us, float temperature_c)
{    
    float speed_of_sound = 331.3 * sqrt(1.0 + temperature_c/273.15);
    float distance = speed_of_sound * ((float)bounce_time_us / 2000.0);
    
    return (uint16_t)distance;
}