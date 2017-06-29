/************************************************************************//**
* @file wiring_digital.c
*
* @version 1.0.0
*
* @author RedBearLab
*
* @date 2016/11/10
*
* @brief Main body of the project.
*
* @copyright Copyright (c) 2012-2016 RedBearLab
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/****************************************************************************
*                HEADER FILES
****************************************************************************/
#include "Arduino.h"
#include "wiring_digital.h"

/****************************************************************************
*                MACRO DEFINITIONS
****************************************************************************/


/****************************************************************************
*                GLOBAL VARIABLES
****************************************************************************/


/****************************************************************************
*                LOCAL VARIABLES
****************************************************************************/


/****************************************************************************
*                LOCAL FUNCTION PROTOTYPES
****************************************************************************/


/****************************************************************************
*                FUNCTION ACHIEVMENT
****************************************************************************/
void pinMode(uint8_t pin, uint8_t mode)
{
    PinName         nrf_pin;
    gpio_t          gpio;
    PinMode         pin_mode;
    PinDirection    direction;

    nrf_pin = Pin_Arduino_to_nRF52(pin);
    MBED_ASSERT(nrf_pin != (PinName)NC);

    gpio.pin = nrf_pin;

    switch(mode) {
        case INPUT :
            direction = PIN_INPUT;
            pin_mode  = PullNone;
        break;

        case OUTPUT :
            direction = PIN_OUTPUT;
            pin_mode  = PullNone;
        break;

        case INPUT_PULLUP :
            direction = PIN_INPUT;
            pin_mode  = PullUp;
        break;

        default :
        return;
    }
    gpio_init(&gpio, nrf_pin);
    gpio_dir(&gpio, direction);
    gpio_mode(&gpio, pin_mode);
}


void digitalWrite(uint8_t pin, uint32_t value)
{
    PinName nrf_pin;

    nrf_pin = Pin_Arduino_to_nRF52(pin);
    MBED_ASSERT(nrf_pin != (PinName)NC);

    if(value)
        NRF_GPIO->OUTSET = (1ul << nrf_pin);
    else
        NRF_GPIO->OUTCLR = (1ul << nrf_pin);
}


uint8_t digitalRead(uint8_t pin)
{
    PinName nrf_pin;

    nrf_pin = Pin_Arduino_to_nRF52(pin);
    MBED_ASSERT(nrf_pin != (PinName)NC);

    if((NRF_GPIO->PIN_CNF[(uint8_t)nrf_pin] & 1ul) == 1ul) {
        // Output mode
        return ( (NRF_GPIO->OUTSET >> nrf_pin) & 1ul );
    }
    else {
        // Input mode
        return ( (NRF_GPIO->IN >> nrf_pin) & 1ul );
    }
}

/****************************************************************************
*                END OF FILE
****************************************************************************/
