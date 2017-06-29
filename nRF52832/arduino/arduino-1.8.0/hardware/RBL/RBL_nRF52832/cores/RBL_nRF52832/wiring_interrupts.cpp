/************************************************************************//**
* @file wiring_interrupts.c
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
#include "wiring_interrupts.h"

/****************************************************************************
*                MACRO DEFINITIONS
****************************************************************************/


/****************************************************************************
*                GLOBAL VARIABLES
****************************************************************************/


/****************************************************************************
*                LOCAL VARIABLES
****************************************************************************/

static interruptHandle_t interruptHandler[31];

/****************************************************************************
*                LOCAL FUNCTION PROTOTYPES
****************************************************************************/


/****************************************************************************
*                FUNCTION ACHIEVMENT
****************************************************************************/

static void gpio_irq_handle_cb(uint32_t id, gpio_irq_event event)
{
    uint8_t pin_state;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;

    interruptHandle_t *pHandler = (interruptHandle_t *)id;

    switch(event) {
        case IRQ_RISE :
            pin_state = ( (NRF_GPIO->IN >> (uint8_t)(pHandler->gpio_irq.ch) ) & 1UL );
            for(cnt1=0; cnt1<100000; cnt1++) {
                if(cnt1 >= 99999) {
                    NVIC_ClearPendingIRQ(GPIOTE_IRQn);
                    return;
                }
                if( ((NRF_GPIO->IN >> (uint8_t)(pHandler->gpio_irq.ch)) & 1UL ) != pin_state ) {
                    pin_state = ((NRF_GPIO->IN >> (uint8_t)(pHandler->gpio_irq.ch)) & 1UL );
                    cnt2 = 0;
                }
                else {
                    if(cnt2++ > 5000)
                        break;
                }
            }

            NVIC_ClearPendingIRQ(GPIOTE_IRQn);
            if( (NRF_GPIO->IN >> (uint8_t)(pHandler->gpio_irq.ch)) & 1UL ) {
                if(pHandler->riseHandle)
                    (pHandler->riseHandle)();
            }
        break;

        case IRQ_FALL :
            pin_state = ( (NRF_GPIO->IN >> (uint8_t)(pHandler->gpio_irq.ch) ) & 1UL );
            for(cnt1=0; cnt1<100000; cnt1++) {
                if(cnt1 >= 99999) {
                    NVIC_ClearPendingIRQ(GPIOTE_IRQn);
                    return;
                }
                if( ((NRF_GPIO->IN >> (uint8_t)(pHandler->gpio_irq.ch)) & 1UL ) != pin_state ) {
                    pin_state = ((NRF_GPIO->IN >> (uint8_t)(pHandler->gpio_irq.ch)) & 1UL );
                    cnt2 = 0;
                }
                else {
                    if(cnt2++ > 5000)
                        break;
                }
            }
            NVIC_ClearPendingIRQ(GPIOTE_IRQn);
            if( ((NRF_GPIO->IN >> (uint8_t)(pHandler->gpio_irq.ch)) & 1UL) == 0x00 ) {
                if(pHandler->fallHandle)
                    (pHandler->fallHandle)();
            }
        break;

        case IRQ_NONE :
        break;
    }
}


void attachInterrupt(uint8_t pin, irqHandle_t handler, uint8_t mode)
{
    PinName nrf_pin;

    nrf_pin = Pin_Arduino_to_nRF52(pin);
    MBED_ASSERT(nrf_pin != (PinName)NC);
    // Check handler
    if(handler == NULL)
        return;
    // Check mode
    if((mode != RISING) && (mode != FALLING) && (mode != CHANGE))
        return;

    // Config interruptHandle_t
    gpio_irq_init(&(interruptHandler[(uint8_t)nrf_pin].gpio_irq), nrf_pin, gpio_irq_handle_cb, (uint32_t)&(interruptHandler[(uint8_t)nrf_pin]));
    gpio_init_in(&(interruptHandler[(uint8_t)nrf_pin].gpio), nrf_pin);

    // Config mode
    if(mode == RISING) {
        interruptHandler[(uint8_t)nrf_pin].riseHandle = handler;
        interruptHandler[(uint8_t)nrf_pin].fallHandle = NULL;

        gpio_irq_set(&(interruptHandler[(uint8_t)nrf_pin].gpio_irq), IRQ_RISE, 1);
    }
    else if(mode == FALLING) {
        interruptHandler[(uint8_t)nrf_pin].riseHandle = NULL;
        interruptHandler[(uint8_t)nrf_pin].fallHandle = handler;

        gpio_irq_set(&(interruptHandler[(uint8_t)nrf_pin].gpio_irq), IRQ_FALL, 1);
    }
    else if(mode == CHANGE) {
        interruptHandler[(uint8_t)nrf_pin].riseHandle = handler;
        interruptHandler[(uint8_t)nrf_pin].fallHandle = handler;

        gpio_irq_set(&(interruptHandler[(uint8_t)nrf_pin].gpio_irq), IRQ_RISE, 1);
        gpio_irq_set(&(interruptHandler[(uint8_t)nrf_pin].gpio_irq), IRQ_FALL, 1);
    }
}

void detachInterrupt(uint8_t pin)
{
    PinName nrf_pin;

    nrf_pin = Pin_Arduino_to_nRF52(pin);
    MBED_ASSERT(nrf_pin != (PinName)NC);

    gpio_irq_free(&interruptHandler[(uint8_t)nrf_pin].gpio_irq);
    memset(&interruptHandler[(uint8_t)nrf_pin], 0x00, sizeof(interruptHandle_t));
    interruptHandler[(uint8_t)nrf_pin].riseHandle = NULL;
    interruptHandler[(uint8_t)nrf_pin].fallHandle = NULL;
}

/****************************************************************************
*                END OF FILE
****************************************************************************/
