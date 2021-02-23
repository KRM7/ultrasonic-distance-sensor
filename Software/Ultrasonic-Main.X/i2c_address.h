#ifndef I2C_ADDRESS_H
#define	I2C_ADDRESS_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "i2c.h"

#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"

uint8_t I2C_Addresses[10];
uint8_t AddressCount = 0;

void I2C_FindAddress(void){
    
    bool ACK = 0;
    
    uint8_t i;
    for(i = 0x00; i < 0xFF; i++){
        I2C_Start();
        ACK = I2C_WriteByte(i << 1);
        I2C_Stop();
        if(ACK){
            I2C_Addresses[AddressCount] = i;
            AddressCount++;
            if(AddressCount == 10) break;
        }
    }
    while(1){
        Nop();
    }    
}


#endif	/* I2C_ADDRESS_H */