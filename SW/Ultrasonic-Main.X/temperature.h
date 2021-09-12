//Functions for the temperature sensor

#ifndef TEMPERATURE_H
#define	TEMPERATURE_H

#include <xc.h> 


//get the analogue output of the temperature sensor converted to 16 bits
uint16_t T_ReadADC(void);

//read the measured temperature value from the sensor (returns temperature in Celsius)
float T_ReadTemperature(void);


#endif	/* TEMPERATURE_H */

