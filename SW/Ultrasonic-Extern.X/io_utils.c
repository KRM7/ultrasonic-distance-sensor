#include "io_utils.h"
#include "xc.h"
#include <math.h>
#include <stdint.h>


uint16_t CalcDistance(uint16_t bounce_time_us, float temperature_c)
{    
    float speed_of_sound = 331.3 * sqrt(1.0 + temperature_c/273.15);
    float distance = speed_of_sound * ((float)bounce_time_us / 2000.0);
    
    return (uint16_t)distance;
}