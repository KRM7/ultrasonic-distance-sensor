/* 
MRF89XAM8A radio transceiver module functions
 */
 
#ifndef MRF89XAM8A_H
#define	MRF89XAM8A_H

#include <xc.h>
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/pin_manager.h"

//register addresses of the radio module
#define GCONREG 0x00
#define DMODREG 0x01
#define FDEVREG 0x02
#define BRSREG 0x03
#define FLTHREG 0x04
#define FIFOCREG 0x05
#define R1CREG 0x06
#define P1CREG 0x07
#define S1CREG 0x08
#define R2CREG 0x09
#define P2CREG 0x0A
#define S2CREG 0x0B
#define PACREG 0x0C
#define FTXRXIREG 0x0D
#define FTPRIREG 0x0E
#define RSTHIREG 0x0F
#define FILCREG 0x10
#define PFCREG 0x11
#define SYNCREG 0x12
#define RESVREG 0x13
#define RSTSREG 0x14
#define OOKCREG 0x15
#define SYNCV31REG 0x16
#define SYNCV23REG 0x17
#define SYNCV15REG 0x18
#define SYNCV07REG 0x19
#define TXCONREG 0x1A
#define CLKOUTREG 0x1B
#define PLOADREG 0x1C
#define NADDSREG 0x1D
#define PKTCREG 0x1E
#define FCRCREG 0x1F

//possible modes of the radio module
typedef enum {
    MODE_TX = 0b100,
    MODE_RX = 0b011,
    MODE_FS = 0b010,
    MODE_STANDBY = 0b001,
    MODE_SLEEP = 0b000
} RF_MODE;


void RF_WriteConfigRegister(uint8_t address, uint8_t value){   
    //address format: 00AAAAA0
    address = address << 0b1;
    address = address & 0b00111110;
    
    nCSCON_SetLow();
    SPI1_Exchange8bit(address);
    SPI1_Exchange8bit(value);
    nCSCON_SetHigh();
}

uint8_t RF_ReadConfigRegister(uint8_t address){
    //address format: 01AAAAA0
    address = address << 0b1;
    address = address & 0b00111110;
    address = address | 0b01000000;
    
    nCSCON_SetLow();
    SPI1_Exchange8bit(address);
    uint8_t value = SPI1_Exchange8bit(0x00);
    nCSCON_SetHigh();
    
    return value;
}

void RF_WriteTransmitFIFO(uint8_t data){
    //write 8 bit data to FIFO
    nCS_SetLow();
    SPI1_Exchange8bit(data);
    nCS_SetHigh();
}

uint8_t RF_ReadReceiveFIFO(void){
    //read 8 bit data from FIFO
    nCS_SetLow();
    uint8_t data = SPI1_Exchange8bit(0x00);
    nCS_SetHigh();
    
    return data;
}

void RF_Initialize(void){
    //General config registers
    //standby mode, 863 MHz, auto Vtune, RPS2 off
    RF_WriteConfigRegister(GCONREG, 0b00110000);
    //FSK modulation, packet mode, (peak mode), max gain (0dB)
    RF_WriteConfigRegister(DMODREG, 0b10101100);
    //f_dev=30.77 kHz (max 40 kHz)
    RF_WriteConfigRegister(FDEVREG, 0b00001101);
    //BitRate=2 kbps
    RF_WriteConfigRegister(BRSREG, 0b01100011);
    //floor threshold for OOK, not used, default
    RF_WriteConfigRegister(FLTHREG, 0b00001100);
    //FIFO size=64byte , FIFO threshold=63byte
    RF_WriteConfigRegister(FIFOCREG, 0b11111111);
    //PLL settings for 868 MHz
    //PLL R=125 (recommended R ~ 119)
    RF_WriteConfigRegister(R1CREG, 0x7D);
    //PLL P=100
    RF_WriteConfigRegister(P1CREG, 0x64);
    //PLL S=20
    RF_WriteConfigRegister(S1CREG, 0x14);
    //not used
    RF_WriteConfigRegister(R2CREG, 0x7D);
    //not used
    RF_WriteConfigRegister(P2CREG, 0x64);
    //not used
    RF_WriteConfigRegister(S2CREG, 0x14);
    
    //rise/fall times in OOK mode, not used (default, 23 us)
    RF_WriteConfigRegister(PACREG, 0b00111000);
    
    //interrupt config registers
    //Receive mode: IRQ1 =: FIFO >= FIFO_THRESHOLD, IRQ0 =: SYNCWORD/ADDRESS match 
    //Transmit mode: IRQ1 =: TXDONE
    //FIFO_FULL, FIFO_EMPTY, FIFO_OVERRUN IRQ disabled
    RF_WriteConfigRegister(FTXRXIREG, 0b11111001);
    //Transmit mode IRQ0 =: FIFO_THRESHOLD, packet transmit start at FIFO>=FIFO_THRESHOLD, RSSI interrupt disabled
    RF_WriteConfigRegister(FTPRIREG, 0b00000111);
    //RSSI interrupt threshold (default, not used)
    RF_WriteConfigRegister(RSTHIREG, 0x00);
    
    //Receiver config registers
    //LPF bandwidth (default, 378 kHz), Butterworth filter value for RX BandWidth=100kHz
    RF_WriteConfigRegister(FILCREG, 0b10100011);
    //f_o = 100 kHz (default/recommended)(polyphase filter center freq)
    RF_WriteConfigRegister(PFCREG, 0b00111000);
    //SYNC word enabled, size=32 bits, max 0 errors
    RF_WriteConfigRegister(SYNCREG, 0b00111000);
    //not used (OOK), default
    RF_WriteConfigRegister(OOKCREG, 0b00000000);
    
    //SYNC word config registers
    //sync value byte1
    RF_WriteConfigRegister(SYNCV31REG, 'S');
    //sync value byte2
    RF_WriteConfigRegister(SYNCV23REG, 'Y');
    //sync value byte3
    RF_WriteConfigRegister(SYNCV15REG, 'N');
    //sync value byte4
    RF_WriteConfigRegister(SYNCV07REG, 'C');
    
    //Transmitter config registers
    //transmit filter f_c=200kHz (default), transmit power = 10 dBm (default)
    RF_WriteConfigRegister(TXCONREG, 0b01110010);
    
    //Oscillator config registers
    //clock out disabled
    RF_WriteConfigRegister(CLKOUTREG, 0b00111100);
    
    //Packet config registers
    //manchester encoding off, packet length = 4 bytes
    RF_WriteConfigRegister(PLOADREG, 0b00000100);
    //node address = 0xD1
    RF_WriteConfigRegister(NADDSREG, 'E');
    //fixed packet length, 4 byte preamble, whitening off, CRC on, address filtering off
    RF_WriteConfigRegister(PKTCREG, 0b00101000);
    //FIFO autoclear on CRC fail on, standby mode FIFO access:write
    RF_WriteConfigRegister(FCRCREG, 0b00000000);
    
    //init
    //PLL unlock
    RF_WriteConfigRegister(FTPRIREG, 0b00000111);
    //frequency synthesiser mode
    RF_WriteConfigRegister(GCONREG, 0b01010000);
    //wait for PLL lock
    //if PLL is unstable we get stuck here
    while(!(RF_ReadConfigRegister(FTPRIREG) & 0b00000010)){
        Nop();
    }
    //standby mode
    RF_WriteConfigRegister(GCONREG, 0b00100111);
}

//set radio mode
void RF_SetMode(RF_MODE mode){
    uint8_t value = RF_ReadConfigRegister(GCONREG);
    value = value & 0b00011111;
    value = (mode << 5) | value;
    RF_WriteConfigRegister(GCONREG, value);
}

//set FIFO threshold for interrupts
void RF_SetFIFOThreshold(uint8_t limit){
    uint8_t value = RF_ReadConfigRegister(FIFOCREG);
    value = value & 0b11000000;
    limit = limit & 0b00111111;
    value = value | limit;
    RF_WriteConfigRegister(FIFOCREG, value);
}

//set packet size in bytes (for packet mode only)
void RF_SetPacketSize(uint8_t size){
    uint8_t value = RF_ReadConfigRegister(PLOADREG);
    value = value & 0b10000000;
    size = size & 0b01111111;
    value = value | size;
    RF_WriteConfigRegister(PLOADREG, value);
}

//set preamble size for packet mode (0-4)
void RF_SetPreambleSize(uint8_t size){    
    uint8_t value = RF_ReadConfigRegister(PKTCREG);
    value = value & 0b10011111;
    size = size & 0b00000011;
    size = size << 5;
    value = value | size;
    RF_WriteConfigRegister(PKTCREG, value);
}

void RF_EnableManchesterEncoding(void){
    uint8_t value = RF_ReadConfigRegister(PLOADREG);
    value = value | 0b10000000;
    RF_WriteConfigRegister(PLOADREG, value);
}

void RF_DisableManchesterEncoding(void){
    uint8_t value = RF_ReadConfigRegister(PLOADREG);
    value = value & 0b01111111;
    RF_WriteConfigRegister(PLOADREG, value);
}

void RF_EnableDataWhitening(void){
    uint8_t value = RF_ReadConfigRegister(PKTCREG);
    value = value | 0b00010000;
    RF_WriteConfigRegister(PKTCREG, value);
}

void RF_DisableDataWhitening(void){
    uint8_t value = RF_ReadConfigRegister(PKTCREG);
    value = value & 0b11101111;
    RF_WriteConfigRegister(PKTCREG, value);    
}

void RF_EnableCRC(void){
    uint8_t value = RF_ReadConfigRegister(PKTCREG);
    value = value | 0b00001000;
    RF_WriteConfigRegister(PKTCREG, value);
}

void RF_DisableCRC(void){
    uint8_t value = RF_ReadConfigRegister(PKTCREG);
    value = value & 0b11110111;
    RF_WriteConfigRegister(PKTCREG, value);    
}

//set transmitter power (0-7), higher value is less power
//111 = -8dBm
//000 = 13dBm
//1 step ~ 3dBm
void RF_SetTransmitPower(uint8_t power){
    uint8_t value = RF_ReadConfigRegister(TXCONREG);
    value = value & 0b11110001;
    power = power & 0b00000111;
    power = power << 1;
    value = value | power;
    RF_WriteConfigRegister(TXCONREG, value);
}

#endif