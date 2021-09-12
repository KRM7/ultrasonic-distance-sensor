#include "eeprom.h"
#include "xc.h"
#include "i2c.h"


void EEPROM_Write(uint16_t mem_addr, uint8_t data)
{
    //get address high and low bytes
    uint8_t mem_addr1 = (uint8_t)(mem_addr >> 8);
    uint8_t mem_addr0 = (uint8_t)mem_addr;
    
    //wait for internal write cycle to complete
    bool dev_ack;
    do
    {
        I2C_Start();
        dev_ack = I2C_WriteByte(EEPROM_MEMORY << 1);
    }
    while(!dev_ack);
    
    //write data to address
    bool addr1_ack = I2C_WriteByte(mem_addr1);
    bool addr0_ack = I2C_WriteByte(mem_addr0);
    bool data_ack = I2C_WriteByte(data);
    
    I2C_Stop();
}

uint8_t EEPROM_RandomRead(uint16_t mem_addr)
{
    //get address high and low bytes
    uint8_t mem_addr1 = (uint8_t)(mem_addr >> 8);
    uint8_t mem_addr0 = (uint8_t)mem_addr;
    
    //set address counter
    bool dev_ack;
    do
    {
        I2C_Start();
        dev_ack = I2C_WriteByte(EEPROM_MEMORY << 1);  
    }
    while(!dev_ack);  
    bool addr1_ack = I2C_WriteByte(mem_addr1);
    bool addr0_ack = I2C_WriteByte(mem_addr0);
    
    //read from address (another start is necessary)
    I2C_Start();
    dev_ack = I2C_WriteByte((EEPROM_MEMORY << 1) | 1);
    uint8_t data = I2C_ReadByte(0);
    I2C_Stop();
    
    return data;
}

uint16_t EEPROM_Initialize()
{
    uint8_t addr_high = EEPROM_RandomRead(0);
    uint8_t addr_low = EEPROM_RandomRead(1);
    
    return ((uint16_t)addr_high << 8) | (uint16_t)addr_low;
}

uint8_t EEPROM_CurrentRead(void)
{
    bool dev_ack;
    do
    {
        I2C_Start();
        dev_ack = I2C_WriteByte((EEPROM_MEMORY << 1) | 1);
    }
    while(!dev_ack);
    
    uint8_t data = I2C_ReadByte(0);
    I2C_Stop();
    
    return data;
}

void EEPROM_PageRead(uint16_t page_num, uint8_t* page)
{
    //get memory address of first byte on the page
    uint8_t mem_addr1 = (uint8_t)(page_num >> 2) & 0b01111111;
    uint8_t mem_addr0 = ((uint8_t)page_num & 0b11) << 6;
    
    //set address counter to the beginning of the page
    bool dev_ack;
    do
    {
        I2C_Start();
        dev_ack = I2C_WriteByte(EEPROM_MEMORY << 1);  
    }
    while(!dev_ack);  
    bool addr1_ack = I2C_WriteByte(mem_addr1);
    bool addr0_ack = I2C_WriteByte(mem_addr0);
    
    //read page
    I2C_Start();
    
    dev_ack = I2C_WriteByte((EEPROM_MEMORY << 1) | 1);
    int i;
    for (i = 0; i < 63; i++)
    {
        page[i] = I2C_ReadByte(1);  //send ACK
    }
    page[63] = I2C_ReadByte(0);     //last byte, no ACK
    
    I2C_Stop();
}

void EEPROM_Write16bits(uint16_t address, uint16_t data)
{
    //rollover
    if (address > EEPROM_ADDRESS_MAX - 1)
    {
        address = 0x0002;
    }
    
    EEPROM_Write(address, (uint8_t)(data >> 8));    //high byte
    EEPROM_Write(address, (uint8_t)data);           //low byte

    //update address counter
    EEPROM_Write(0, (address + 2) >> 8);
    EEPROM_Write(1, (address + 2));
}