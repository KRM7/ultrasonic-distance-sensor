//Központi egység

#include "mcc_generated_files/mcc.h"
#include "MRF89XAM8A.h"
#include "LCD.h"
#include "i2c.h"
#include "EEPROM.h"
#include <math.h>

#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"

//device mode
typedef enum{
    SYSTEM = 0b0,
    SINGLE = 0b1
} DEVICE_MODE;
volatile DEVICE_MODE MODE = SYSTEM;

//measurement data
volatile bool SIGNAL;
volatile float DIST = 0;
volatile uint16_t TIME = 0;
volatile float TEMP_MAIN = 0;
volatile float TEMP_EXTERN = 0;

//radio mode
volatile RF_MODE radio_mode = MODE_TX;

//USB
static uint8_t readBuffer[64];
static uint8_t writeBuffer[64];
#define USB_EEPROM_READ_REQUEST 0x7A

//functions
void IO_InterruptHandler(void);
uint16_t ReadADC(void);
float ReadTemperature(void);
void TriggerPulse(void);
char NumToChar(uint8_t num);
void USBtransfer(void);

int main(void)
{
    //initialize the device
    __delay_ms(10);
    SYSTEM_Initialize();
    I2C_Init();
    TMR2_Start();
        
    //RF module init
    RF_Initialize();
    radio_mode = MODE_STANDBY;
    RF_SetMode(radio_mode);
    RF_SetFIFOThreshold(4);
    RF_SetPacketSize(4);
    //RF_SetPreambleSize(4);
    //RF_EnableManchesterEncoding();
    //RF_EnableDataWhitening();
    //RF_EnableCRC();
    //RF_SetTransmitPower(0b000);
    
    //LCD init
    LCD_Initialize();
    LCD_Home();
    LCD_PutChar('D');
    LCD_PutChar('i');
    LCD_PutChar('s');
    LCD_PutChar('t');
    LCD_PutChar(':');
    LCD_PutChar(' ');
    LCD_SetCursor(0x40);
    LCD_PutChar('T');
    LCD_PutChar('e');
    LCD_PutChar('m');
    LCD_PutChar('p');
    LCD_PutChar(':');
    LCD_PutChar(' ');
    
    //init temp
    TEMP_MAIN = ReadTemperature();
    TEMP_EXTERN = TEMP_MAIN;
    
    //init eeprom
    EEPROM_Initialize();
    
    CN_SetInterruptHandler(IO_InterruptHandler);

    while (1){
        
        //send trigger
        SIGNAL = false;
        TriggerPulse();
        __delay_ms(60);
        
        if(SIGNAL && TIME < 40000)
        {
            //transmit mode
            radio_mode = MODE_TX;
            RF_SetMode(MODE_TX);
            RF_SetFIFOThreshold(2);
            //send time
            RF_WriteTransmitFIFO(TIME >> 8);
            RF_WriteTransmitFIFO(TIME);
            //send temperature
            int16_t temp = (int16_t)((TEMP_MAIN + 40) * 10); //(T+40)*10 in int
            uint16_t tempu = (uint16_t)temp;
            RF_WriteTransmitFIFO(tempu >> 8);
            RF_WriteTransmitFIFO(tempu);

            USBtransfer();
            __delay_ms(450);    
        }
     
    }

    return 1;
}

void IO_InterruptHandler(void){ //ultrasonic sensor, radio, button interrupts are handled here
    
    uint16_t porta = PORTA;
    uint16_t portb = PORTB;
    
    bool ECHO = porta & 16;
    bool RF0 = porta & 1;
    bool RF1 = portb & 4;
    bool MEAS = portb & 128;
    
    //echo signal interrupt
    if(ECHO){
        TMR2 = 58; //offset error correction
        while(ECHO_GetValue()); //distance~ECHO_HIGH
        TIME = TMR2; //time in us
        TEMP_MAIN = ReadTemperature();
        SIGNAL = true;
        //LED_MODE_Toggle();
    }
    
    //transmit mode radio interrupts
    else if(radio_mode == MODE_TX){
        if(RF0){ //FIFO >= FIFO_THRESHOLD interrupt (packet ready)
            //LED_MODE_Toggle();
        }
        if(RF1){ //TX DONE interrupt
            //switch to RX mode
            //LED_MODE_Toggle();
            radio_mode = MODE_RX;
            RF_SetMode(MODE_RX);
            RF_SetFIFOThreshold(3);
        }
    }
    //receiver mode radio interrupts
    else if(radio_mode == MODE_RX){
        if(RF0){ //SYNC or ADDRESS match interrupt
            //LED_MODE_Toggle();
        }
        if(RF1){ //FIFO > FIFO_THRESHOLD interrupt (packet received)
            //get answer
            LED_MODE_Toggle();
            uint8_t CMD1 = RF_ReadReceiveFIFO();
            uint8_t CMD0 = RF_ReadReceiveFIFO();
            uint8_t TEMP1 = RF_ReadReceiveFIFO();
            uint8_t TEMP0 = RF_ReadReceiveFIFO();
            
            //calculate temperature
            uint16_t tempu = ((uint16_t)TEMP1 << 8) | (uint16_t)TEMP0; ////(T+40)*10 in uint
            int16_t temp = (int16_t)tempu;
            TEMP_EXTERN = (float)temp/10 - 40.0; //TEMP in C
            
            //calculate distance in mm
            //float SPEED_OF_SOUND = 331.3*sqrt(1+(TEMP_MAIN+TEMP_EXTERN)/2/273.15);  //speed of sound at TEMP
            float SPEED_OF_SOUND = 331.3*sqrt(1+(TEMP_MAIN)/273.15);  //speed of sound at TEMP
            DIST = (SPEED_OF_SOUND/2)*((float)TIME / 1000000)*1000;  //distance in mm (min 2cm max 4m)

            //write result in eeprom (distance in mm in 16bit)(every 1 sec)
            static bool b = 0;
            if(b){
                EEPROM_Write16bits((uint16_t)DIST);
            }
            b++;
            
            //display results on LCD
            //first line
            LCD_SetCursor(0x06);
            if((int)DIST >= 1000) LCD_PutChar(NumToChar(((int)DIST/1000) % 10));
            if((int)DIST >= 100) LCD_PutChar(NumToChar(((int)DIST/100) % 10));
            if((int)DIST >= 10) LCD_PutChar(NumToChar(((int)DIST/10) % 10));
            LCD_PutChar(NumToChar((int)DIST % 10));
            LCD_PutChar(' ');
            LCD_PutChar('m');
            LCD_PutChar('m');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            //second line
            LCD_SetCursor(0x46);
            int16_t T = (int16_t)(TEMP_MAIN +0.5);
            if(T < 0){
                LCD_PutChar('-');
                T = -T;
            }
            if(T >= 100) LCD_PutChar(NumToChar((T/100) % 10));
            if(T >= 10) LCD_PutChar(NumToChar((T/10) % 10));
            LCD_PutChar(NumToChar(T % 10));
            LCD_PutChar(' ');
            LCD_PutChar('C');
            LCD_PutChar(' ');
            LCD_PutChar(' ');
            
            //standby mode until next measurement
            radio_mode = MODE_STANDBY;
            RF_SetMode(MODE_STANDBY);   
        }
    }
     
//    else if(MEAS && MODE){
//        __delay_ms(15);         //debounce delay
//        if(MEAS_GetValue()){    //MEAS button interrupt
//            //TriggerPulse();     //send trigger pulse
//            //TMR2 = 0;           //timer start
//        }
//    }
}

uint16_t ReadADC(void){   
    ADC1_ChannelSelect(TEMP);
    ADC1_SoftwareTriggerEnable();
    __delay_us(1);
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(TEMP));
    uint16_t ADC_result = ADC1_ConversionResultGet(TEMP);
    
    return ADC_result;
}

float ReadTemperature(void){
    //reads temperature from thermistor IC
    int ADC_diff = ReadADC() - 230; //ADC out is ~230 at ~21C, temperatures are compared to these values
    float Vdiff = 3.3*(float)ADC_diff / 1024; 
    float TEMP = 21 + 100*Vdiff; //10mV~1C
   
    return TEMP;
}

void TriggerPulse(void){
    TRIG_SetHigh();
    __delay_us(10);
    TRIG_SetLow();
}

char NumToChar(uint8_t num){
    return num + '0';
}

void USBtransfer(void){
    
    if(USBGetDeviceState() < CONFIGURED_STATE) return;
    if(USBIsDeviceSuspended()== true) return;
    
    if(USBUSARTIsTxTrfReady() == true){
        uint8_t i;
        uint8_t numBytesRead;
        bool readRequest = false;

        //usb read
        numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));

        for(i=0; i<numBytesRead; i++){
            switch(readBuffer[i])
            {
                case USB_EEPROM_READ_REQUEST:
                    readRequest = true;
                    break;
                default:
                    break;
            }
        }

        //usb write
        if(numBytesRead > 0 && readRequest){
            //read and send entire eeprom memory
            uint16_t i, j;
            uint8_t *p;
            
            //send entire eeprom memory
            for(i=0; i<512; i++){
                //read one page
                p = EEPROM_PageRead(i);
                
                //send page
                for(j=0; j<64; j++){
                    writeBuffer[j] = *(p+j);
                }
                putUSBUSART(writeBuffer, sizeof(writeBuffer));
                CDCTxService();
            }       
        }
    }
}

/*END OF FILE*/