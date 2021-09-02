//for I2C LCDs using the ST7032 controller
//MCCOG21605B6W-FPTLWI
//no error handling

#ifndef LCD_H
#define	LCD_H

#include <xc.h>
#include "i2c.h"

#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"

//I2C
#define LCD_ADDR 0b01111100 //write only
bool LCD_ADDR_ACK = 0;
bool LCD_CTRL_ACK = 0;
bool LCD_CMD_ACK = 0;

//possible control bytes
#define LCD_INSTRUCTION 0x00
#define LCD_DRAM 0x40

void LCD_I2C_Write(uint8_t ctrl, uint8_t data){
    I2C_Start();
    LCD_ADDR_ACK = I2C_WriteByte(LCD_ADDR); //Address
    LCD_CTRL_ACK = I2C_WriteByte(ctrl);     //control byte
    LCD_CMD_ACK = I2C_WriteByte(data);      //data byte
    I2C_Stop();
}

void LCD_Initialize(void){
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

//clear the LCD
void LCD_Clear(void){
    LCD_I2C_Write(LCD_INSTRUCTION, 0x01);  
}

//move the cursor to line 1, char 1
void LCD_Home(void){
    LCD_I2C_Write(LCD_INSTRUCTION, 0x02);
}

//turn the LCD off
void LCD_Off(void){
    LCD_I2C_Write(LCD_INSTRUCTION, 0x08);
}

//turn the LCD on
void LCD_On(void){
    LCD_I2C_Write(LCD_INSTRUCTION, 0x0C);
}

//move cursor to given dram address
//line 1 dram addresses: from 0x00
//line 2 dram addresses: from 0x40
void LCD_SetCursor(uint8_t dram_addr){
    dram_addr = dram_addr | 0b10000000;
    LCD_I2C_Write(LCD_INSTRUCTION, dram_addr);
}

//write character to current dram address
void LCD_PutChar(char c){
    LCD_I2C_Write(LCD_DRAM, c);
}

//write entire line
void LCD_WriteLine(bool line, char s[16]){
    int i;
    switch(line){
        case 0: //line 1
            LCD_Home();
            for(i=0; i<16; i++){
                LCD_PutChar(s[i]);
            }
            break;
        case 1: //line 2
            LCD_SetCursor(0x40);
            for(i=0; i<16; i++){
                LCD_PutChar(s[i]);
            }
            break;
        default:
            break;
    }
}

#endif	/* LCD_H */

