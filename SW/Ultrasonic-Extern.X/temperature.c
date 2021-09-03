#include "xc.h"
#include "temperature.h"
#include "mcc_generated_files/adc1.h"

//for the delays
#include "mcc_generated_files/clock.h"
#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"


uint16_t T_ReadADC(void)
{   
    //select the channel of the temperature sensor
    ADC1_ChannelSelect(TEMP);
    
    //start conversion
    ADC1_SoftwareTriggerEnable();
    __delay_us(1);
    ADC1_SoftwareTriggerDisable();
    
    //wait for the end of the conversion
    while (!ADC1_IsConversionComplete(TEMP));
    
    uint16_t ADC_result = ADC1_ConversionResultGet(TEMP);
    
    return ADC_result;
}

float T_ReadTemperature(void)
{
    //ADCout is ~300 at ~21C, temperatures are compared to these values for better precision
    int adc_diff = T_ReadADC() - 300;
    
    static const float Vdd = 2.6;
    static const uint16_t adc_resolution = 1024;
    
    float Vdiff = Vdd * (float)adc_diff / (float)adc_resolution;
    
    //10mV diff ~ 1C diff
    float temperature = 21.0 + 100.0 * Vdiff;
   
    return temperature;
}