#include "xc.h"
#include "lcd.h"
#include "i2c.h"

//for the delays
#include "mcc_generated_files/clock.h"
#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"


void LCD_I2C_Write(LCD_CNTRL ctrl, uint8_t data)
{
    I2C_Start();
    I2C_WriteByte(LCD_ADDR); //address
    I2C_WriteByte(ctrl);     //control byte
    I2C_WriteByte(data);     //data byte
    I2C_Stop();
}

void LCD_Initialize(void)
{
    //init sequence as described in the datasheet
    __delay_ms(40);
    LCD_I2C_Write(LCD_INSTRUCTION, 0x38); //function set, 2 line, 5x8 font size, instruction table 0
    __delay_us(30);
    LCD_I2C_Write(LCD_INSTRUCTION, 0x39); //function set, 2 line, 5x8 font size, instruction table 1
    __delay_us(30);
    LCD_I2C_Write(LCD_INSTRUCTION, 0x14); //internal OSC freq
    __delay_us(30);
    LCD_I2C_Write(LCD_INSTRUCTION, 0x71); //set contrast
    __delay_us(30);
    LCD_I2C_Write(LCD_INSTRUCTION, 0x54); //power, icon, contrast
    __delay_us(30);
    LCD_I2C_Write(LCD_INSTRUCTION, 0x6F); //follower control
    __delay_ms(200);
    LCD_I2C_Write(LCD_INSTRUCTION, 0x0C); //display on, cursor off, blinking off
    __delay_us(30);
    LCD_I2C_Write(LCD_INSTRUCTION, 0x01); //clear display
}

void LCD_Clear(void)
{
    LCD_I2C_Write(LCD_INSTRUCTION, 0x01);  
}

void LCD_TurnOff(void)
{
    LCD_I2C_Write(LCD_INSTRUCTION, 0x08);
}

void LCD_TurnOn(void)
{
    LCD_I2C_Write(LCD_INSTRUCTION, 0x0C);
}

void LCD_MoveCursor(uint8_t line, uint8_t pos)
{
    uint8_t dram_addr = line + pos - 1;
    dram_addr = dram_addr | 0b10000000;
    LCD_I2C_Write(LCD_INSTRUCTION, dram_addr);
}

void LCD_Home(void)
{
    LCD_MoveCursor(LCD_LINE1, 1);
}

void LCD_PutChar(char c)
{
    LCD_I2C_Write(LCD_DRAM, c);
}

void LCD_WriteStrFrom(uint8_t line, uint8_t pos, const char* str, uint8_t num_chars)
{
    LCD_MoveCursor(line, pos);
    
    int i;
    for (i = 0; i < num_chars; i++)
    {
        LCD_PutChar(str[i]);
    }
}