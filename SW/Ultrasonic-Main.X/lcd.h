//Functions for I2C LCDs using the ST7032 controller
//MCCOG21605B6W-FPTLWI

#ifndef LCD_H
#define	LCD_H

#include <xc.h>

//the I2C address of the LCD, write only
#define LCD_ADDR 0b01111100

//the possible control bytes
typedef enum {
    LCD_INSTRUCTION = 0x00, //send an instruction
    LCD_DRAM = 0x40         //write to DRAM
} LCD_CNTRL;

//the DRAM addresses of the first character on each line
#define LCD_LINE1 0x00
#define LCD_LINE2 0x40


//general function used to send a command to the LCD
//each command consists of 2 bytes (not counting the address), a control and a data byte
//the control byte depends on whether we are writing to the DRAM, or sending an instruction to the LCD
void LCD_I2C_Write(LCD_CNTRL ctrl, uint8_t data);

//initialize the LCD (with a clear display)
void LCD_Initialize(void);

//clear the LCD
void LCD_Clear(void);

//turn the LCD off
void LCD_TurnOff(void);

//turn the LCD on
void LCD_TurnOn(void);

//move the cursor to given position
//there are 16 characters on each line, and the first character is pos = 1
void LCD_MoveCursor(uint8_t line, uint8_t pos);

//move the cursor to line 1, char 1
void LCD_Home(void);

//write character to the current DRAM address
void LCD_PutChar(char c);

//write string of characters to the LCD starting from the specified location
void LCD_WriteStrFrom(uint8_t line, uint8_t pos, const char* str, uint8_t num_chars);

#endif	/* LCD_H */

