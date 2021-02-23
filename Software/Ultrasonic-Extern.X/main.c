//Távoli egység

#include "mcc_generated_files/mcc.h"
#include "MRF89XAM8A.h"
#include <math.h>

#define FCY (_XTAL_FREQ / 2)
#include "libpic30.h"

//device mode
typedef enum{
    SYSTEM = 0b0,
    SINGLE = 0b1
} DEVICE_MODE;
volatile DEVICE_MODE MODE = SYSTEM;

//7 segment display
int current_display_pos = 2;
#define incrementDisplayPos() (current_display_pos = (current_display_pos + 1) % 3)
uint16_t DISPLAY_VALUE = 123;
#define DIGIT1 ((int)(DISPLAY_VALUE/100) % 10)
#define DIGIT2 ((int)(DISPLAY_VALUE/10) % 10)
#define DIGIT3 (DISPLAY_VALUE % 10)

//measurement data
volatile float DIST = 0;
volatile uint16_t TIME = 0;
volatile float TEMP_MAIN = 0;
volatile float TEMP_EXTERN = 0;

//radio mode
volatile RF_MODE radio_mode;


//functions
void IO_InterruptHandler(void);
void T1_InterruptHandler(void);
void displayClockPulse(void);
void displayDigit(int digit);
void displayNumber(int number); //for testing
uint16_t readADC(void);
float readTemperature(void);

int main(void)
{
    // initialize the device
    __delay_ms(10);
    SYSTEM_Initialize();
    RF_Initialize();
    
    //init radio
    radio_mode = MODE_RX;
    RF_SetMode(radio_mode);
    RF_SetFIFOThreshold(3);
    RF_SetPacketSize(4);
    //RF_SetPreambleSize(4);
    //RF_EnableManchesterEncoding();
    //RF_EnableDataWhitening();
    //RF_EnableCRC();
    //RF_SetTransmitPower(0b000);
    
    //init temp
    TEMP_MAIN = readTemperature();
    TEMP_EXTERN = TEMP_MAIN;
    
    CN_SetInterruptHandler(IO_InterruptHandler);
    TMR1_SetInterruptHandler(T1_InterruptHandler);

    while (1)
    {
        if(radio_mode == MODE_STANDBY){
            int16_t temp = (int16_t)((TEMP_EXTERN + 40) * 10); //(T+40)*10 in int
            uint16_t tempu = (uint16_t)temp;
            radio_mode = MODE_TX;
            RF_SetMode(radio_mode);
            RF_SetFIFOThreshold(2);
            RF_WriteTransmitFIFO(0x00);
            RF_WriteTransmitFIFO(0x00);                          
            RF_WriteTransmitFIFO(tempu >> 8);
            RF_WriteTransmitFIFO(tempu);
        }
        
        if(DIST < 250) LED_WARN1_SetHigh();
        else LED_WARN1_SetLow();
        if(DIST < 500) LED_WARN2_SetHigh();
        else LED_WARN2_SetLow();
    }

    return 1;
}


void IO_InterruptHandler(void){
    
    uint16_t porta = PORTA;
    uint16_t portb = PORTB;
    
    bool RF0 = portb & 16384; //RB14
    bool RF1 = portb & 8; //RB3
    bool SW = porta & 4; //RA2
    
    //transmit mode radio interrupts
    if(radio_mode == MODE_TX){
        if(RF0){ //FIFO >= FIFO_THRESHOLD interrupt (TX START)
            //LED_MODE_Toggle();
        }
        if(RF1){ //TX DONE interrupt
            //switch back to RX mode
            radio_mode = MODE_RX;
            RF_SetMode(MODE_RX);
            RF_SetFIFOThreshold(3);
            LED_MODE_Toggle();
        }
    }
    //receiver mode radio interrupts
    else if(radio_mode == MODE_RX){
        if(RF0){ //SYNC or ADDRESS match interrupt
        }
        if(RF1){ //FIFO > FIFO_THRESHOLD interrupt (packet received)
            uint8_t TIME1 = RF_ReadReceiveFIFO();
            uint8_t TIME0 = RF_ReadReceiveFIFO();
            uint8_t TEMP1 = RF_ReadReceiveFIFO();
            uint8_t TEMP0 = RF_ReadReceiveFIFO();
            
            //calculate temperature
            uint16_t tempu = ((uint16_t)TEMP1 << 8) | (uint16_t)TEMP0; ////(T+40)*10 in uint
            int16_t temp = (int16_t)tempu;
            TEMP_MAIN = (float)temp/10 - 40.0; //TEMP in C
            TEMP_EXTERN = readTemperature();
            
            //calculate and display distance in cm
            TIME = ((uint16_t)TIME1 << 8) + (uint16_t)TIME0;        //time in us
            float SPEED_OF_SOUND = 331.3*sqrt(1+(TEMP_MAIN+TEMP_EXTERN)/2/273.15);  //speed of sound at TEMP
            DIST = (SPEED_OF_SOUND/2)*((float)TIME / 1000000)*100;  //distance in cm (min 2cm max 4m)
            
            //display
            DISPLAY_VALUE = DIST;
            
            radio_mode = MODE_STANDBY;
        }
    }
    
//    else if(SW){ //MODE button pressed
//        __delay_ms(15); //debounce delay
//        if(SW_MODE_GetValue()){         
//        }
//    }
}

void T1_InterruptHandler(void){
    //handles the 7 segment display  
    incrementDisplayPos(); //0-2 cycle
    displayClockPulse();
    switch (current_display_pos){
        case 0:
            displayDigit(DIGIT1);
            break;
        case 1:
            displayDigit(DIGIT2);
            break;
        case 2:
            displayDigit(DIGIT3);
            break;
        default:
            break;
    }
}

void displayClockPulse(void){
    //increments decade counter by 1 //switches digits on 7 segment   
    CNTR_CLK_SetHigh();
    __delay_us(2); //min 0.3 us
    CNTR_CLK_SetLow();
}

void displayDigit(int digit){
    //displays 1 digit on the 7 segment display
    _LATB7 = (digit & ( 1 << 0 )) >> 0; //LED_A
    _LATB8 = (digit & ( 1 << 1 )) >> 1; //LED_B
    _LATB9 = (digit & ( 1 << 2 )) >> 2; //LED_C
    _LATB6 = (digit & ( 1 << 3 )) >> 3; //LED_D
}

void displayNumber(int number){
    //displays 3 digit number on the 7 segment display
    //not needed in final program
    int last_digit = number % 10;
    int middle_digit = (int)(number/10) % 10;
    int first_digit = (int)(number/100) % 10;
    
    displayDigit(first_digit);
    __delay_ms(6);
    displayClockPulse();
    incrementDisplayPos();
    
    displayDigit(middle_digit);
    __delay_ms(6);
    displayClockPulse();
    incrementDisplayPos();
    
    displayDigit(last_digit);
    __delay_ms(6);
    displayClockPulse();
    incrementDisplayPos();
}

uint16_t readADC(void){
    
    ADC1_ChannelSelect(TEMP);
    ADC1_SoftwareTriggerEnable();
    __delay_us(1);
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(TEMP));
    uint16_t ADC_result = ADC1_ConversionResultGet(TEMP);
    
    return ADC_result;
}

float readTemperature(void){
    //reads temperature from thermistor IC
    float Vref_p = 2.6;
    int ADC_diff = readADC() - 300; //ADC out is 300 at 21C
    float Vdiff = Vref_p*(float)ADC_diff / 1024; 
    float TEMP = 21 + 100*Vdiff;
   
    return TEMP;
}