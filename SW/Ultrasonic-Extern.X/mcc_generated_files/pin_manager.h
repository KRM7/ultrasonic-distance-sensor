/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  PIC24FJ64GA002
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>

/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RA0, high using LATA0.

  @Description
    Sets the GPIO pin, RA0, high using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA0 high (1)
    LED_WARN1_SetHigh();
    </code>

*/
#define LED_WARN1_SetHigh()          (_LATA0 = 1)
/**
  @Summary
    Sets the GPIO pin, RA0, low using LATA0.

  @Description
    Sets the GPIO pin, RA0, low using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA0 low (0)
    LED_WARN1_SetLow();
    </code>

*/
#define LED_WARN1_SetLow()           (_LATA0 = 0)
/**
  @Summary
    Toggles the GPIO pin, RA0, using LATA0.

  @Description
    Toggles the GPIO pin, RA0, using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA0
    LED_WARN1_Toggle();
    </code>

*/
#define LED_WARN1_Toggle()           (_LATA0 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RA0.

  @Description
    Reads the value of the GPIO pin, RA0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA0
    postValue = LED_WARN1_GetValue();
    </code>

*/
#define LED_WARN1_GetValue()         _RA0
/**
  @Summary
    Configures the GPIO pin, RA0, as an input.

  @Description
    Configures the GPIO pin, RA0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA0 as an input
    LED_WARN1_SetDigitalInput();
    </code>

*/
#define LED_WARN1_SetDigitalInput()  (_TRISA0 = 1)
/**
  @Summary
    Configures the GPIO pin, RA0, as an output.

  @Description
    Configures the GPIO pin, RA0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA0 as an output
    LED_WARN1_SetDigitalOutput();
    </code>

*/
#define LED_WARN1_SetDigitalOutput() (_TRISA0 = 0)
/**
  @Summary
    Sets the GPIO pin, RA1, high using LATA1.

  @Description
    Sets the GPIO pin, RA1, high using LATA1.

  @Preconditions
    The RA1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA1 high (1)
    RF_RST_SetHigh();
    </code>

*/
#define RF_RST_SetHigh()          (_LATA1 = 1)
/**
  @Summary
    Sets the GPIO pin, RA1, low using LATA1.

  @Description
    Sets the GPIO pin, RA1, low using LATA1.

  @Preconditions
    The RA1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA1 low (0)
    RF_RST_SetLow();
    </code>

*/
#define RF_RST_SetLow()           (_LATA1 = 0)
/**
  @Summary
    Toggles the GPIO pin, RA1, using LATA1.

  @Description
    Toggles the GPIO pin, RA1, using LATA1.

  @Preconditions
    The RA1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA1
    RF_RST_Toggle();
    </code>

*/
#define RF_RST_Toggle()           (_LATA1 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RA1.

  @Description
    Reads the value of the GPIO pin, RA1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA1
    postValue = RF_RST_GetValue();
    </code>

*/
#define RF_RST_GetValue()         _RA1
/**
  @Summary
    Configures the GPIO pin, RA1, as an input.

  @Description
    Configures the GPIO pin, RA1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA1 as an input
    RF_RST_SetDigitalInput();
    </code>

*/
#define RF_RST_SetDigitalInput()  (_TRISA1 = 1)
/**
  @Summary
    Configures the GPIO pin, RA1, as an output.

  @Description
    Configures the GPIO pin, RA1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA1 as an output
    RF_RST_SetDigitalOutput();
    </code>

*/
#define RF_RST_SetDigitalOutput() (_TRISA1 = 0)
/**
  @Summary
    Sets the GPIO pin, RA2, high using LATA2.

  @Description
    Sets the GPIO pin, RA2, high using LATA2.

  @Preconditions
    The RA2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA2 high (1)
    SW_MODE_SetHigh();
    </code>

*/
#define SW_MODE_SetHigh()          (_LATA2 = 1)
/**
  @Summary
    Sets the GPIO pin, RA2, low using LATA2.

  @Description
    Sets the GPIO pin, RA2, low using LATA2.

  @Preconditions
    The RA2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA2 low (0)
    SW_MODE_SetLow();
    </code>

*/
#define SW_MODE_SetLow()           (_LATA2 = 0)
/**
  @Summary
    Toggles the GPIO pin, RA2, using LATA2.

  @Description
    Toggles the GPIO pin, RA2, using LATA2.

  @Preconditions
    The RA2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA2
    SW_MODE_Toggle();
    </code>

*/
#define SW_MODE_Toggle()           (_LATA2 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RA2.

  @Description
    Reads the value of the GPIO pin, RA2.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA2
    postValue = SW_MODE_GetValue();
    </code>

*/
#define SW_MODE_GetValue()         _RA2
/**
  @Summary
    Configures the GPIO pin, RA2, as an input.

  @Description
    Configures the GPIO pin, RA2, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA2 as an input
    SW_MODE_SetDigitalInput();
    </code>

*/
#define SW_MODE_SetDigitalInput()  (_TRISA2 = 1)
/**
  @Summary
    Configures the GPIO pin, RA2, as an output.

  @Description
    Configures the GPIO pin, RA2, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA2 as an output
    SW_MODE_SetDigitalOutput();
    </code>

*/
#define SW_MODE_SetDigitalOutput() (_TRISA2 = 0)
/**
  @Summary
    Sets the GPIO pin, RA3, high using LATA3.

  @Description
    Sets the GPIO pin, RA3, high using LATA3.

  @Preconditions
    The RA3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA3 high (1)
    LED_MODE_SetHigh();
    </code>

*/
#define LED_MODE_SetHigh()          (_LATA3 = 1)
/**
  @Summary
    Sets the GPIO pin, RA3, low using LATA3.

  @Description
    Sets the GPIO pin, RA3, low using LATA3.

  @Preconditions
    The RA3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA3 low (0)
    LED_MODE_SetLow();
    </code>

*/
#define LED_MODE_SetLow()           (_LATA3 = 0)
/**
  @Summary
    Toggles the GPIO pin, RA3, using LATA3.

  @Description
    Toggles the GPIO pin, RA3, using LATA3.

  @Preconditions
    The RA3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA3
    LED_MODE_Toggle();
    </code>

*/
#define LED_MODE_Toggle()           (_LATA3 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RA3.

  @Description
    Reads the value of the GPIO pin, RA3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA3
    postValue = LED_MODE_GetValue();
    </code>

*/
#define LED_MODE_GetValue()         _RA3
/**
  @Summary
    Configures the GPIO pin, RA3, as an input.

  @Description
    Configures the GPIO pin, RA3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA3 as an input
    LED_MODE_SetDigitalInput();
    </code>

*/
#define LED_MODE_SetDigitalInput()  (_TRISA3 = 1)
/**
  @Summary
    Configures the GPIO pin, RA3, as an output.

  @Description
    Configures the GPIO pin, RA3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA3 as an output
    LED_MODE_SetDigitalOutput();
    </code>

*/
#define LED_MODE_SetDigitalOutput() (_TRISA3 = 0)
/**
  @Summary
    Sets the GPIO pin, RA4, high using LATA4.

  @Description
    Sets the GPIO pin, RA4, high using LATA4.

  @Preconditions
    The RA4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA4 high (1)
    LED_WARN2_SetHigh();
    </code>

*/
#define LED_WARN2_SetHigh()          (_LATA4 = 1)
/**
  @Summary
    Sets the GPIO pin, RA4, low using LATA4.

  @Description
    Sets the GPIO pin, RA4, low using LATA4.

  @Preconditions
    The RA4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA4 low (0)
    LED_WARN2_SetLow();
    </code>

*/
#define LED_WARN2_SetLow()           (_LATA4 = 0)
/**
  @Summary
    Toggles the GPIO pin, RA4, using LATA4.

  @Description
    Toggles the GPIO pin, RA4, using LATA4.

  @Preconditions
    The RA4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA4
    LED_WARN2_Toggle();
    </code>

*/
#define LED_WARN2_Toggle()           (_LATA4 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RA4.

  @Description
    Reads the value of the GPIO pin, RA4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA4
    postValue = LED_WARN2_GetValue();
    </code>

*/
#define LED_WARN2_GetValue()         _RA4
/**
  @Summary
    Configures the GPIO pin, RA4, as an input.

  @Description
    Configures the GPIO pin, RA4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA4 as an input
    LED_WARN2_SetDigitalInput();
    </code>

*/
#define LED_WARN2_SetDigitalInput()  (_TRISA4 = 1)
/**
  @Summary
    Configures the GPIO pin, RA4, as an output.

  @Description
    Configures the GPIO pin, RA4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA4 as an output
    LED_WARN2_SetDigitalOutput();
    </code>

*/
#define LED_WARN2_SetDigitalOutput() (_TRISA4 = 0)
/**
  @Summary
    Sets the GPIO pin, RB10, high using LATB10.

  @Description
    Sets the GPIO pin, RB10, high using LATB10.

  @Preconditions
    The RB10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB10 high (1)
    LATCH_EN_SetHigh();
    </code>

*/
#define LATCH_EN_SetHigh()          (_LATB10 = 1)
/**
  @Summary
    Sets the GPIO pin, RB10, low using LATB10.

  @Description
    Sets the GPIO pin, RB10, low using LATB10.

  @Preconditions
    The RB10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB10 low (0)
    LATCH_EN_SetLow();
    </code>

*/
#define LATCH_EN_SetLow()           (_LATB10 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB10, using LATB10.

  @Description
    Toggles the GPIO pin, RB10, using LATB10.

  @Preconditions
    The RB10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB10
    LATCH_EN_Toggle();
    </code>

*/
#define LATCH_EN_Toggle()           (_LATB10 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB10.

  @Description
    Reads the value of the GPIO pin, RB10.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB10
    postValue = LATCH_EN_GetValue();
    </code>

*/
#define LATCH_EN_GetValue()         _RB10
/**
  @Summary
    Configures the GPIO pin, RB10, as an input.

  @Description
    Configures the GPIO pin, RB10, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB10 as an input
    LATCH_EN_SetDigitalInput();
    </code>

*/
#define LATCH_EN_SetDigitalInput()  (_TRISB10 = 1)
/**
  @Summary
    Configures the GPIO pin, RB10, as an output.

  @Description
    Configures the GPIO pin, RB10, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB10 as an output
    LATCH_EN_SetDigitalOutput();
    </code>

*/
#define LATCH_EN_SetDigitalOutput() (_TRISB10 = 0)
/**
  @Summary
    Sets the GPIO pin, RB11, high using LATB11.

  @Description
    Sets the GPIO pin, RB11, high using LATB11.

  @Preconditions
    The RB11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB11 high (1)
    CNTR_CLK_SetHigh();
    </code>

*/
#define CNTR_CLK_SetHigh()          (_LATB11 = 1)
/**
  @Summary
    Sets the GPIO pin, RB11, low using LATB11.

  @Description
    Sets the GPIO pin, RB11, low using LATB11.

  @Preconditions
    The RB11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB11 low (0)
    CNTR_CLK_SetLow();
    </code>

*/
#define CNTR_CLK_SetLow()           (_LATB11 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB11, using LATB11.

  @Description
    Toggles the GPIO pin, RB11, using LATB11.

  @Preconditions
    The RB11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB11
    CNTR_CLK_Toggle();
    </code>

*/
#define CNTR_CLK_Toggle()           (_LATB11 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB11.

  @Description
    Reads the value of the GPIO pin, RB11.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB11
    postValue = CNTR_CLK_GetValue();
    </code>

*/
#define CNTR_CLK_GetValue()         _RB11
/**
  @Summary
    Configures the GPIO pin, RB11, as an input.

  @Description
    Configures the GPIO pin, RB11, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB11 as an input
    CNTR_CLK_SetDigitalInput();
    </code>

*/
#define CNTR_CLK_SetDigitalInput()  (_TRISB11 = 1)
/**
  @Summary
    Configures the GPIO pin, RB11, as an output.

  @Description
    Configures the GPIO pin, RB11, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB11 as an output
    CNTR_CLK_SetDigitalOutput();
    </code>

*/
#define CNTR_CLK_SetDigitalOutput() (_TRISB11 = 0)
/**
  @Summary
    Sets the GPIO pin, RB12, high using LATB12.

  @Description
    Sets the GPIO pin, RB12, high using LATB12.

  @Preconditions
    The RB12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB12 high (1)
    SCLK_SetHigh();
    </code>

*/
#define SCLK_SetHigh()          (_LATB12 = 1)
/**
  @Summary
    Sets the GPIO pin, RB12, low using LATB12.

  @Description
    Sets the GPIO pin, RB12, low using LATB12.

  @Preconditions
    The RB12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB12 low (0)
    SCLK_SetLow();
    </code>

*/
#define SCLK_SetLow()           (_LATB12 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB12, using LATB12.

  @Description
    Toggles the GPIO pin, RB12, using LATB12.

  @Preconditions
    The RB12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB12
    SCLK_Toggle();
    </code>

*/
#define SCLK_Toggle()           (_LATB12 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB12.

  @Description
    Reads the value of the GPIO pin, RB12.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB12
    postValue = SCLK_GetValue();
    </code>

*/
#define SCLK_GetValue()         _RB12
/**
  @Summary
    Configures the GPIO pin, RB12, as an input.

  @Description
    Configures the GPIO pin, RB12, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB12 as an input
    SCLK_SetDigitalInput();
    </code>

*/
#define SCLK_SetDigitalInput()  (_TRISB12 = 1)
/**
  @Summary
    Configures the GPIO pin, RB12, as an output.

  @Description
    Configures the GPIO pin, RB12, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB12 as an output
    SCLK_SetDigitalOutput();
    </code>

*/
#define SCLK_SetDigitalOutput() (_TRISB12 = 0)
/**
  @Summary
    Sets the GPIO pin, RB13, high using LATB13.

  @Description
    Sets the GPIO pin, RB13, high using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB13 high (1)
    MOSI_SetHigh();
    </code>

*/
#define MOSI_SetHigh()          (_LATB13 = 1)
/**
  @Summary
    Sets the GPIO pin, RB13, low using LATB13.

  @Description
    Sets the GPIO pin, RB13, low using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB13 low (0)
    MOSI_SetLow();
    </code>

*/
#define MOSI_SetLow()           (_LATB13 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB13, using LATB13.

  @Description
    Toggles the GPIO pin, RB13, using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB13
    MOSI_Toggle();
    </code>

*/
#define MOSI_Toggle()           (_LATB13 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB13.

  @Description
    Reads the value of the GPIO pin, RB13.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB13
    postValue = MOSI_GetValue();
    </code>

*/
#define MOSI_GetValue()         _RB13
/**
  @Summary
    Configures the GPIO pin, RB13, as an input.

  @Description
    Configures the GPIO pin, RB13, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB13 as an input
    MOSI_SetDigitalInput();
    </code>

*/
#define MOSI_SetDigitalInput()  (_TRISB13 = 1)
/**
  @Summary
    Configures the GPIO pin, RB13, as an output.

  @Description
    Configures the GPIO pin, RB13, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB13 as an output
    MOSI_SetDigitalOutput();
    </code>

*/
#define MOSI_SetDigitalOutput() (_TRISB13 = 0)
/**
  @Summary
    Sets the GPIO pin, RB14, high using LATB14.

  @Description
    Sets the GPIO pin, RB14, high using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 high (1)
    RF_IRQ0_SetHigh();
    </code>

*/
#define RF_IRQ0_SetHigh()          (_LATB14 = 1)
/**
  @Summary
    Sets the GPIO pin, RB14, low using LATB14.

  @Description
    Sets the GPIO pin, RB14, low using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 low (0)
    RF_IRQ0_SetLow();
    </code>

*/
#define RF_IRQ0_SetLow()           (_LATB14 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB14, using LATB14.

  @Description
    Toggles the GPIO pin, RB14, using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB14
    RF_IRQ0_Toggle();
    </code>

*/
#define RF_IRQ0_Toggle()           (_LATB14 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB14.

  @Description
    Reads the value of the GPIO pin, RB14.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB14
    postValue = RF_IRQ0_GetValue();
    </code>

*/
#define RF_IRQ0_GetValue()         _RB14
/**
  @Summary
    Configures the GPIO pin, RB14, as an input.

  @Description
    Configures the GPIO pin, RB14, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an input
    RF_IRQ0_SetDigitalInput();
    </code>

*/
#define RF_IRQ0_SetDigitalInput()  (_TRISB14 = 1)
/**
  @Summary
    Configures the GPIO pin, RB14, as an output.

  @Description
    Configures the GPIO pin, RB14, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an output
    RF_IRQ0_SetDigitalOutput();
    </code>

*/
#define RF_IRQ0_SetDigitalOutput() (_TRISB14 = 0)
/**
  @Summary
    Sets the GPIO pin, RB15, high using LATB15.

  @Description
    Sets the GPIO pin, RB15, high using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 high (1)
    TEMP_SetHigh();
    </code>

*/
#define TEMP_SetHigh()          (_LATB15 = 1)
/**
  @Summary
    Sets the GPIO pin, RB15, low using LATB15.

  @Description
    Sets the GPIO pin, RB15, low using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 low (0)
    TEMP_SetLow();
    </code>

*/
#define TEMP_SetLow()           (_LATB15 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB15, using LATB15.

  @Description
    Toggles the GPIO pin, RB15, using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB15
    TEMP_Toggle();
    </code>

*/
#define TEMP_Toggle()           (_LATB15 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB15.

  @Description
    Reads the value of the GPIO pin, RB15.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB15
    postValue = TEMP_GetValue();
    </code>

*/
#define TEMP_GetValue()         _RB15
/**
  @Summary
    Configures the GPIO pin, RB15, as an input.

  @Description
    Configures the GPIO pin, RB15, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an input
    TEMP_SetDigitalInput();
    </code>

*/
#define TEMP_SetDigitalInput()  (_TRISB15 = 1)
/**
  @Summary
    Configures the GPIO pin, RB15, as an output.

  @Description
    Configures the GPIO pin, RB15, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an output
    TEMP_SetDigitalOutput();
    </code>

*/
#define TEMP_SetDigitalOutput() (_TRISB15 = 0)
/**
  @Summary
    Sets the GPIO pin, RB2, high using LATB2.

  @Description
    Sets the GPIO pin, RB2, high using LATB2.

  @Preconditions
    The RB2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB2 high (1)
    nCSCON_SetHigh();
    </code>

*/
#define nCSCON_SetHigh()          (_LATB2 = 1)
/**
  @Summary
    Sets the GPIO pin, RB2, low using LATB2.

  @Description
    Sets the GPIO pin, RB2, low using LATB2.

  @Preconditions
    The RB2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB2 low (0)
    nCSCON_SetLow();
    </code>

*/
#define nCSCON_SetLow()           (_LATB2 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB2, using LATB2.

  @Description
    Toggles the GPIO pin, RB2, using LATB2.

  @Preconditions
    The RB2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB2
    nCSCON_Toggle();
    </code>

*/
#define nCSCON_Toggle()           (_LATB2 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB2.

  @Description
    Reads the value of the GPIO pin, RB2.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB2
    postValue = nCSCON_GetValue();
    </code>

*/
#define nCSCON_GetValue()         _RB2
/**
  @Summary
    Configures the GPIO pin, RB2, as an input.

  @Description
    Configures the GPIO pin, RB2, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB2 as an input
    nCSCON_SetDigitalInput();
    </code>

*/
#define nCSCON_SetDigitalInput()  (_TRISB2 = 1)
/**
  @Summary
    Configures the GPIO pin, RB2, as an output.

  @Description
    Configures the GPIO pin, RB2, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB2 as an output
    nCSCON_SetDigitalOutput();
    </code>

*/
#define nCSCON_SetDigitalOutput() (_TRISB2 = 0)
/**
  @Summary
    Sets the GPIO pin, RB3, high using LATB3.

  @Description
    Sets the GPIO pin, RB3, high using LATB3.

  @Preconditions
    The RB3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB3 high (1)
    RF_IRQ1_SetHigh();
    </code>

*/
#define RF_IRQ1_SetHigh()          (_LATB3 = 1)
/**
  @Summary
    Sets the GPIO pin, RB3, low using LATB3.

  @Description
    Sets the GPIO pin, RB3, low using LATB3.

  @Preconditions
    The RB3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB3 low (0)
    RF_IRQ1_SetLow();
    </code>

*/
#define RF_IRQ1_SetLow()           (_LATB3 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB3, using LATB3.

  @Description
    Toggles the GPIO pin, RB3, using LATB3.

  @Preconditions
    The RB3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB3
    RF_IRQ1_Toggle();
    </code>

*/
#define RF_IRQ1_Toggle()           (_LATB3 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB3.

  @Description
    Reads the value of the GPIO pin, RB3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB3
    postValue = RF_IRQ1_GetValue();
    </code>

*/
#define RF_IRQ1_GetValue()         _RB3
/**
  @Summary
    Configures the GPIO pin, RB3, as an input.

  @Description
    Configures the GPIO pin, RB3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB3 as an input
    RF_IRQ1_SetDigitalInput();
    </code>

*/
#define RF_IRQ1_SetDigitalInput()  (_TRISB3 = 1)
/**
  @Summary
    Configures the GPIO pin, RB3, as an output.

  @Description
    Configures the GPIO pin, RB3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB3 as an output
    RF_IRQ1_SetDigitalOutput();
    </code>

*/
#define RF_IRQ1_SetDigitalOutput() (_TRISB3 = 0)
/**
  @Summary
    Sets the GPIO pin, RB4, high using LATB4.

  @Description
    Sets the GPIO pin, RB4, high using LATB4.

  @Preconditions
    The RB4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB4 high (1)
    nCS_SetHigh();
    </code>

*/
#define nCS_SetHigh()          (_LATB4 = 1)
/**
  @Summary
    Sets the GPIO pin, RB4, low using LATB4.

  @Description
    Sets the GPIO pin, RB4, low using LATB4.

  @Preconditions
    The RB4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB4 low (0)
    nCS_SetLow();
    </code>

*/
#define nCS_SetLow()           (_LATB4 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB4, using LATB4.

  @Description
    Toggles the GPIO pin, RB4, using LATB4.

  @Preconditions
    The RB4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB4
    nCS_Toggle();
    </code>

*/
#define nCS_Toggle()           (_LATB4 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB4.

  @Description
    Reads the value of the GPIO pin, RB4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB4
    postValue = nCS_GetValue();
    </code>

*/
#define nCS_GetValue()         _RB4
/**
  @Summary
    Configures the GPIO pin, RB4, as an input.

  @Description
    Configures the GPIO pin, RB4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB4 as an input
    nCS_SetDigitalInput();
    </code>

*/
#define nCS_SetDigitalInput()  (_TRISB4 = 1)
/**
  @Summary
    Configures the GPIO pin, RB4, as an output.

  @Description
    Configures the GPIO pin, RB4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB4 as an output
    nCS_SetDigitalOutput();
    </code>

*/
#define nCS_SetDigitalOutput() (_TRISB4 = 0)
/**
  @Summary
    Sets the GPIO pin, RB5, high using LATB5.

  @Description
    Sets the GPIO pin, RB5, high using LATB5.

  @Preconditions
    The RB5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB5 high (1)
    MISO_SetHigh();
    </code>

*/
#define MISO_SetHigh()          (_LATB5 = 1)
/**
  @Summary
    Sets the GPIO pin, RB5, low using LATB5.

  @Description
    Sets the GPIO pin, RB5, low using LATB5.

  @Preconditions
    The RB5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB5 low (0)
    MISO_SetLow();
    </code>

*/
#define MISO_SetLow()           (_LATB5 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB5, using LATB5.

  @Description
    Toggles the GPIO pin, RB5, using LATB5.

  @Preconditions
    The RB5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB5
    MISO_Toggle();
    </code>

*/
#define MISO_Toggle()           (_LATB5 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB5.

  @Description
    Reads the value of the GPIO pin, RB5.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB5
    postValue = MISO_GetValue();
    </code>

*/
#define MISO_GetValue()         _RB5
/**
  @Summary
    Configures the GPIO pin, RB5, as an input.

  @Description
    Configures the GPIO pin, RB5, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB5 as an input
    MISO_SetDigitalInput();
    </code>

*/
#define MISO_SetDigitalInput()  (_TRISB5 = 1)
/**
  @Summary
    Configures the GPIO pin, RB5, as an output.

  @Description
    Configures the GPIO pin, RB5, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB5 as an output
    MISO_SetDigitalOutput();
    </code>

*/
#define MISO_SetDigitalOutput() (_TRISB5 = 0)
/**
  @Summary
    Sets the GPIO pin, RB6, high using LATB6.

  @Description
    Sets the GPIO pin, RB6, high using LATB6.

  @Preconditions
    The RB6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB6 high (1)
    LED_D_SetHigh();
    </code>

*/
#define LED_D_SetHigh()          (_LATB6 = 1)
/**
  @Summary
    Sets the GPIO pin, RB6, low using LATB6.

  @Description
    Sets the GPIO pin, RB6, low using LATB6.

  @Preconditions
    The RB6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB6 low (0)
    LED_D_SetLow();
    </code>

*/
#define LED_D_SetLow()           (_LATB6 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB6, using LATB6.

  @Description
    Toggles the GPIO pin, RB6, using LATB6.

  @Preconditions
    The RB6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB6
    LED_D_Toggle();
    </code>

*/
#define LED_D_Toggle()           (_LATB6 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB6.

  @Description
    Reads the value of the GPIO pin, RB6.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB6
    postValue = LED_D_GetValue();
    </code>

*/
#define LED_D_GetValue()         _RB6
/**
  @Summary
    Configures the GPIO pin, RB6, as an input.

  @Description
    Configures the GPIO pin, RB6, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB6 as an input
    LED_D_SetDigitalInput();
    </code>

*/
#define LED_D_SetDigitalInput()  (_TRISB6 = 1)
/**
  @Summary
    Configures the GPIO pin, RB6, as an output.

  @Description
    Configures the GPIO pin, RB6, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB6 as an output
    LED_D_SetDigitalOutput();
    </code>

*/
#define LED_D_SetDigitalOutput() (_TRISB6 = 0)
/**
  @Summary
    Sets the GPIO pin, RB7, high using LATB7.

  @Description
    Sets the GPIO pin, RB7, high using LATB7.

  @Preconditions
    The RB7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB7 high (1)
    LED_A_SetHigh();
    </code>

*/
#define LED_A_SetHigh()          (_LATB7 = 1)
/**
  @Summary
    Sets the GPIO pin, RB7, low using LATB7.

  @Description
    Sets the GPIO pin, RB7, low using LATB7.

  @Preconditions
    The RB7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB7 low (0)
    LED_A_SetLow();
    </code>

*/
#define LED_A_SetLow()           (_LATB7 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB7, using LATB7.

  @Description
    Toggles the GPIO pin, RB7, using LATB7.

  @Preconditions
    The RB7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB7
    LED_A_Toggle();
    </code>

*/
#define LED_A_Toggle()           (_LATB7 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB7.

  @Description
    Reads the value of the GPIO pin, RB7.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB7
    postValue = LED_A_GetValue();
    </code>

*/
#define LED_A_GetValue()         _RB7
/**
  @Summary
    Configures the GPIO pin, RB7, as an input.

  @Description
    Configures the GPIO pin, RB7, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB7 as an input
    LED_A_SetDigitalInput();
    </code>

*/
#define LED_A_SetDigitalInput()  (_TRISB7 = 1)
/**
  @Summary
    Configures the GPIO pin, RB7, as an output.

  @Description
    Configures the GPIO pin, RB7, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB7 as an output
    LED_A_SetDigitalOutput();
    </code>

*/
#define LED_A_SetDigitalOutput() (_TRISB7 = 0)
/**
  @Summary
    Sets the GPIO pin, RB8, high using LATB8.

  @Description
    Sets the GPIO pin, RB8, high using LATB8.

  @Preconditions
    The RB8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB8 high (1)
    LED_B_SetHigh();
    </code>

*/
#define LED_B_SetHigh()          (_LATB8 = 1)
/**
  @Summary
    Sets the GPIO pin, RB8, low using LATB8.

  @Description
    Sets the GPIO pin, RB8, low using LATB8.

  @Preconditions
    The RB8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB8 low (0)
    LED_B_SetLow();
    </code>

*/
#define LED_B_SetLow()           (_LATB8 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB8, using LATB8.

  @Description
    Toggles the GPIO pin, RB8, using LATB8.

  @Preconditions
    The RB8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB8
    LED_B_Toggle();
    </code>

*/
#define LED_B_Toggle()           (_LATB8 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB8.

  @Description
    Reads the value of the GPIO pin, RB8.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB8
    postValue = LED_B_GetValue();
    </code>

*/
#define LED_B_GetValue()         _RB8
/**
  @Summary
    Configures the GPIO pin, RB8, as an input.

  @Description
    Configures the GPIO pin, RB8, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB8 as an input
    LED_B_SetDigitalInput();
    </code>

*/
#define LED_B_SetDigitalInput()  (_TRISB8 = 1)
/**
  @Summary
    Configures the GPIO pin, RB8, as an output.

  @Description
    Configures the GPIO pin, RB8, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB8 as an output
    LED_B_SetDigitalOutput();
    </code>

*/
#define LED_B_SetDigitalOutput() (_TRISB8 = 0)
/**
  @Summary
    Sets the GPIO pin, RB9, high using LATB9.

  @Description
    Sets the GPIO pin, RB9, high using LATB9.

  @Preconditions
    The RB9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB9 high (1)
    LED_C_SetHigh();
    </code>

*/
#define LED_C_SetHigh()          (_LATB9 = 1)
/**
  @Summary
    Sets the GPIO pin, RB9, low using LATB9.

  @Description
    Sets the GPIO pin, RB9, low using LATB9.

  @Preconditions
    The RB9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB9 low (0)
    LED_C_SetLow();
    </code>

*/
#define LED_C_SetLow()           (_LATB9 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB9, using LATB9.

  @Description
    Toggles the GPIO pin, RB9, using LATB9.

  @Preconditions
    The RB9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB9
    LED_C_Toggle();
    </code>

*/
#define LED_C_Toggle()           (_LATB9 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB9.

  @Description
    Reads the value of the GPIO pin, RB9.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB9
    postValue = LED_C_GetValue();
    </code>

*/
#define LED_C_GetValue()         _RB9
/**
  @Summary
    Configures the GPIO pin, RB9, as an input.

  @Description
    Configures the GPIO pin, RB9, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB9 as an input
    LED_C_SetDigitalInput();
    </code>

*/
#define LED_C_SetDigitalInput()  (_TRISB9 = 1)
/**
  @Summary
    Configures the GPIO pin, RB9, as an output.

  @Description
    Configures the GPIO pin, RB9, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB9 as an output
    LED_C_SetDigitalOutput();
    </code>

*/
#define LED_C_SetDigitalOutput() (_TRISB9 = 0)

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the PIC24FJ64GA002
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize (void);

/**
  @Summary
    Callback for IOC Pins.

  @Description
    This routine is callback for IOC Pins.

  @Param
    None.

  @Returns
    None
 
  @Example 
    <code>
        CN_SetInterruptHandler(&CN_CallBack);
    </code>
*/
void CN_CallBack(void);

/**
  @Summary
    Assigns a function pointer with a callback address.

  @Description
    This routine assigns a function pointer with a callback address.

  @Param
    Address of the callback routine.

  @Returns
    None
 
  @Example 
    <code>
        CN_SetInterruptHandler(&CN_CallBack);
    </code>
*/
void CN_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Assigns a function pointer with a callback address.

  @Description
    This routine assigns a function pointer with a callback address.

  @Param
    Address of the callback routine.

  @Returns
    None
 
  @Example 
    <code>
        CN_SetIOCInterruptHandler(&CN_CallBack);
    </code>
*/
void __attribute__((deprecated("\nThis will be removed in future MCC releases. \nUse CN_SetInterruptHandler instead."))) CN_SetIOCInterruptHandler(void *handler);

#endif
