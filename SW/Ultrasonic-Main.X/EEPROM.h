//I2C EEPROM functions
//M24256-BRDW6TP
//no error handling

//TODO: check page read

#ifndef EEPROM_H
#define	EEPROM_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "i2c.h"

#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"

//eeprom
#define EEPROM_NUM_OF_PAGES 512 //64 byte on each page
uint16_t EEPROM_ADDRESS_COUNTER = 0x0002;

//i2c
#define EEPROM_MEMORY 0b1010000 //I2C address of EEPROM
bool EEPROM_DEV_ACK = 0;
bool EEPROM_ADDR1_ACK = 0;
bool EEPROM_ADDR0_ACK = 0;
bool EEPROM_DATA_ACK = 0;

//write data to a specific address
void EEPROM_Write(uint16_t mem_addr, uint8_t data){
    //get address high and low bytes
    uint8_t mem_addr1 = (uint8_t)(mem_addr >> 8);
    uint8_t mem_addr0 = (uint8_t)mem_addr;
    do{ //wait for internal write cycle to complete
        I2C_Start();
        EEPROM_DEV_ACK = I2C_WriteByte(EEPROM_MEMORY << 1);
    }
    while(!EEPROM_DEV_ACK);
    EEPROM_ADDR1_ACK = I2C_WriteByte(mem_addr1);
    EEPROM_ADDR0_ACK = I2C_WriteByte(mem_addr0);
    EEPROM_DATA_ACK = I2C_WriteByte(data);
    I2C_Stop();
    //__delay_ms(5); //wait internal write cycle delay if no polling is used
}

//read value from a specific address
uint8_t EEPROM_RandomRead(uint16_t mem_addr){
    //get address high and low bytes
    uint8_t mem_addr1 = (uint8_t)(mem_addr >> 8);
    uint8_t mem_addr0 = (uint8_t)mem_addr;
    //set address counter
    do{
        I2C_Start();
        EEPROM_DEV_ACK = I2C_WriteByte(EEPROM_MEMORY << 1);  
    }
    while(!EEPROM_DEV_ACK);
    EEPROM_ADDR1_ACK = I2C_WriteByte(mem_addr1);
    EEPROM_ADDR0_ACK = I2C_WriteByte(mem_addr0);
    //read from address
    I2C_Start();
    EEPROM_DEV_ACK = I2C_WriteByte((EEPROM_MEMORY << 1) | 1);
    uint8_t data = I2C_ReadByte(0);
    I2C_Stop();
    
    return data;
}

//read value from current memory address
uint8_t EEPROM_CurrentRead(void){
    I2C_Start();
    EEPROM_DEV_ACK = I2C_WriteByte((EEPROM_MEMORY << 1) | 1);
    uint8_t data = I2C_ReadByte(0);
    I2C_Stop();
    
    return data;
}

//read entire page (64 bytes)
//valid page numbers are 0-511
uint8_t* EEPROM_PageRead(uint16_t page_num){
    static uint8_t page[64];
    //get memory address of first byte on the page
    uint8_t mem_addr1 = (uint8_t)(page_num >> 2) & 0b01111111;
    uint8_t mem_addr0 = ((uint8_t)page_num & 0b11) << 6;
    
    //set address counter to the beginning of the page
    do{
        I2C_Start();
        EEPROM_DEV_ACK = I2C_WriteByte(EEPROM_MEMORY << 1);  
    }
    while(!EEPROM_DEV_ACK);
    EEPROM_ADDR1_ACK = I2C_WriteByte(mem_addr1);
    EEPROM_ADDR0_ACK = I2C_WriteByte(mem_addr0);
    //read page
    I2C_Start();
    EEPROM_DEV_ACK = I2C_WriteByte((EEPROM_MEMORY << 1) | 1);
    int i;
    for(i=0; i<63; i++){
        page[i]=I2C_ReadByte(1); //send ACK
    }
    page[63] = I2C_ReadByte(0); //last byte, no ACK
    I2C_Stop();
    
    return page;
}

//init eeprom
void EEPROM_Initialize(){
    uint8_t addr_high = EEPROM_RandomRead(0x0000);
    uint8_t addr_low = EEPROM_RandomRead(0x0001);
    EEPROM_ADDRESS_COUNTER = (uint16_t)(addr_high << 8) | (uint16_t)addr_low;
}

//write 2 bytes to current address
void EEPROM_Write16bits(uint16_t data){
    if(EEPROM_ADDRESS_COUNTER > 0x7FFE) EEPROM_ADDRESS_COUNTER = 0x0002;    //rollover
    EEPROM_Write(EEPROM_ADDRESS_COUNTER, (uint8_t)(data >> 8));             //write high byte
    EEPROM_Write(EEPROM_ADDRESS_COUNTER, (uint8_t)data);                    //write low byte
    EEPROM_ADDRESS_COUNTER += 2;
    EEPROM_Write(0x0000, EEPROM_ADDRESS_COUNTER >> 8);
    EEPROM_Write(0x0001, EEPROM_ADDRESS_COUNTER);
}

#endif	/* EEPROM_H */

