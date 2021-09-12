//MRF89XAM8A radio transceiver module functions
 
#ifndef MRF89XAM8A_H
#define	MRF89XAM8A_H

#include <xc.h>

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
    MODE_TX = 0b100,        //transmit
    MODE_RX = 0b011,        //receive
    MODE_FS = 0b010,        //freq. synthesizer
    MODE_STANDBY = 0b001,
    MODE_SLEEP = 0b000
} RF_MODE;


//set the radio module one of the radio module's register to a value.
void RF_WriteConfigRegister(uint8_t address, uint8_t value);

//read the value of one of the radio module's registers
uint8_t RF_ReadConfigRegister(uint8_t address);

//write 8 bit data to the transmit FIFO of the radio module
void RF_WriteTransmitFIFO(uint8_t data);

//read 8 bits of data from the receive FIFO of the radio module
uint8_t RF_ReadReceiveFIFO(void);

//initialize the radio module
void RF_Initialize(void);

//set the radio mode
void RF_SetMode(RF_MODE mode);

//set FIFO threshold for interrupts
void RF_SetFIFOThreshold(uint8_t limit);

//set packet size in bytes (for packet mode only)
void RF_SetPacketSize(uint8_t size);

//set preamble size for packet mode (0-4)
void RF_SetPreambleSize(uint8_t size);

void RF_EnableManchesterEncoding(void);
void RF_DisableManchesterEncoding(void);

void RF_EnableDataWhitening(void);
void RF_DisableDataWhitening(void);

void RF_EnableCRC(void);
void RF_DisableCRC(void);

//set the transmitter power (0-7), higher value is less power
// 0b111 (7) = -8dBm
// 0b000 (0) = 13dBm
// 1 step ~ 3dBm
void RF_SetTransmitPower(uint8_t power);


#endif