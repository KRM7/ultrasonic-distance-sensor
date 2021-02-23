//I2C MASTER
#ifndef I2C_MASTER_H
#define	I2C_MASTER_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"

//SCL : RB8
//SDA : RB9

#define I2C_delay()   (__delay_us(50)) //set I2C clock T/2  100kHz=500, 400kHz=125, 1MHz=50
#define getSDA()      (_RB9)
#define getSDA_DIR()  (_TRISB9)

#define SDA_HIGH()  (_LATB9 = 1)    //set SDA pin high
#define SDA_LOW()   (_LATB9 = 0)    //set SDA pin low
#define SCL_HIGH()  (_LATB8 = 1)    //set SCL pin high
#define SCL_LOW()   (_LATB8 = 0)    //set SCL pin low


inline void I2C_Init(void){
    ODCBbits.ODB8 = 1;  //SCL open drain
    ODCBbits.ODB9 = 1;  //SDA open drain  
    _TRISB8 = 0;        //SCL output
    _TRISB9 = 0;        //SDA output
    SDA_HIGH();
    SCL_HIGH();    
}

//generate start condition
inline void I2C_Start(void){
    SDA_HIGH();
    SCL_HIGH();
    I2C_delay();
    SDA_LOW();
    I2C_delay();  
    SCL_LOW();
    I2C_delay();
}

//generate stop condition
inline void I2C_Stop(void){
    SDA_LOW();
    I2C_delay();
    SCL_HIGH();
    I2C_delay();
    SDA_HIGH();
    I2C_delay();
}

//write 1 bit
inline void I2C_WriteBit(bool b){   
    if(b) SDA_HIGH();
    else SDA_LOW();
    I2C_delay();
    SCL_HIGH();
    I2C_delay();
    SCL_LOW();    
}

//read 1 bit
inline bool I2C_ReadBit(void){
    
    bool  b;
    
    SDA_HIGH();
    I2C_delay();
    SCL_HIGH();
    I2C_delay();
    b = getSDA();
    SCL_LOW();
    
    return b;
}

//write one byte, returns ACK bit
bool I2C_WriteByte(uint8_t data){
    
    bool ACK = 0;
    
    uint8_t i;
    for(i=0; i<8; i++){
        I2C_WriteBit(data & 0x80); //write MSB
        data <<= 1;
    }
    
    ACK = !I2C_ReadBit(); //check for slave acknowledge
 
    return ACK;
}

//read one byte
uint8_t I2C_ReadByte(bool ACK){
    
    uint8_t data = 0;
    
    uint8_t i;
    for(i=0; i<8; i++){
        data <<= 1;
        data = data | I2C_ReadBit();
    }
    
    if(ACK) I2C_WriteBit(0);
    else I2C_WriteBit(1);
    
    return data;
}

#endif	/* I2C__MASTER_H */