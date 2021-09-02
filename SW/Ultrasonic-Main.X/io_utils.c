#include "io_utils.h"
#include "xc.h"
#include <math.h>


void DistanceToStr(float distance, char* out_str)
{
    //the distance is always positive and 4 digits at most   
    out_str[0] = distance >= 1000.0 ? DigitToChar(GetDigit(distance, 3)) : ' ';
    out_str[1] = distance >= 100.0 ? DigitToChar(GetDigit(distance, 2)) : ' ';
    out_str[2] = distance >= 10.0 ? DigitToChar(GetDigit(distance, 1)) : ' ';
    out_str[3] = DigitToChar(GetDigit(distance, 0));
    out_str[4] = ' ';
    out_str[5] = 'm';
    out_str[6] = 'm';
}

void TemperatureToStr(float temperature, char* out_str)
{
    //the temperature can be negative and is at most 2 digits  
    out_str[0] = temperature < 0.0 ? '-' : ' ';
    out_str[1] = temperature > 10.0 ? DigitToChar(GetDigit(temperature, 1)) : ' ';
    out_str[2] = DigitToChar(GetDigit(temperature, 0));
    out_str[3] = ' ';
    out_str[4] = 'C';
}

float CalcDistance(float bounce_time_us, float temperature_c)
{    
    float speed_of_sound = 331.3 * sqrt(1.0 + temperature_c/273.15);
    
    return speed_of_sound * (bounce_time_us / 2000.0);
}