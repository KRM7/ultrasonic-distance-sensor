//I2C EEPROM functions
//M24256-BRDW6TP

#ifndef EEPROM_H
#define	EEPROM_H

#include <xc.h>

#define EEPROM_NUM_PAGES 512        //with 64 byte on each page
#define EEPROM_ADDRESS_MAX 0x7FFF   //highest valid EEPROM memory array address

//I2C address of EEPROM
#define EEPROM_MEMORY 0b1010000


//write data to a specific address
void EEPROM_Write(uint16_t mem_addr, uint8_t data);

//read value from a specific address
uint8_t EEPROM_RandomRead(uint16_t mem_addr);

//initialize the EEPROM, returns the first empty address
uint16_t EEPROM_Initialize();

//read data from the current memory address
uint8_t EEPROM_CurrentRead(void);

//read an entire page (64 bytes)
//valid page numbers are 0-511
void EEPROM_PageRead(uint16_t page_num, uint8_t* page);

//write 2 bytes to current address
void EEPROM_Write16bits(uint16_t address, uint16_t data);


#endif	/* EEPROM_H */