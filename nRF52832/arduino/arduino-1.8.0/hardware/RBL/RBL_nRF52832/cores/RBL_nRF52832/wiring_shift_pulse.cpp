/************************************************************************//**
* @file wiring_shift_pulse.c
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
#include "wiring_shift_pulse.h"

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
// See pulse_asm.S
extern unsigned long countPulseASM(const volatile uint32_t *port, uint32_t bit, uint32_t stateMask, unsigned long maxloops);


/****************************************************************************
*                FUNCTION ACHIEVMENT
****************************************************************************/
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, BitOrder bitOrder)
{
    uint8_t value;
    uint8_t index;

    value = 0;
    for(index=0; index<8; index++) {
        digitalWrite(clockPin, HIGH);
        if(bitOrder == LSBFIRST)
            value |= (digitalRead(dataPin) << index);
        else
            value |= (digitalRead(dataPin) << (7 - index));
        // Set clock to LOW
        digitalWrite(clockPin, LOW);
    }
    return value;
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, BitOrder bitOrder, uint8_t value)
{
    uint8_t index;

    for(index=0; index<8; index++) {
        if(bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(value & (1 << index)));
        else
            digitalWrite(dataPin, !!(value & (1 << (7 - index))));

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse. */
uint32_t pulseIn(uint8_t pin, uint8_t state, uint32_t timeout)
{
    uint8_t nrf_pin;

    pinMode(pin, INPUT);
    nrf_pin = (uint8_t)Pin_Arduino_to_nRF52(pin);
    if(nrf_pin > 31)
        return 0;
    // cache the port and bit of the pin in order to speed up the
    // pulse width measuring loop and achieve finer resolution.  calling
    // digitalRead() instead yields much coarser resolution.
    // PinDescription p = g_APinDescription[pin];
    uint32_t bit = 1 << nrf_pin; //p.ulPin;
    uint32_t stateMask = state ? bit : 0;

    // convert the timeout from microseconds to a number of times through
    // the initial loop; it takes (roughly) 13 clock cycles per iteration.
    uint32_t maxloops = microsecondsToClockCycles(timeout) / 13;

    uint32_t width = countPulseASM(&(NRF_GPIO->IN), bit, stateMask, maxloops);

    // convert the reading to microseconds. The loop has been determined
    // to be 13 clock cycles long and have about 16 clocks between the edge
    // and the start of the loop. There will be some error introduced by
    // the interrupt handlers.
    if (width)
        return clockCyclesToMicroseconds(width * 13 + 16);
    else
        return 0;
}

uint32_t pulseInLong(uint8_t pin, uint8_t state, uint32_t timeout)
{
    uint8_t nrf_pin;

    pinMode(pin, INPUT);
    nrf_pin = (uint8_t)Pin_Arduino_to_nRF52(pin);
    if(nrf_pin > 31)
        return 0;

    uint32_t bit = 1 << nrf_pin;
    uint32_t stateMask = state ? bit : 0;

    uint32_t startMicros = micros();

    // wait for any previous pulse to end
    while((NRF_GPIO->IN & bit) == stateMask) {
        if((micros() - startMicros) > timeout)
            return 0;
    }

    // wait for the pulse to start
    while((NRF_GPIO->IN & bit) != stateMask) {
        if((micros() - startMicros) > timeout)
            return 0;
    }

    uint32_t start = micros();
    // wait for the pulse to stop
    while ((NRF_GPIO->IN & bit) == stateMask) {
        if (micros() - startMicros > timeout)
            return 0;
    }

    return micros() - start;
}
/****************************************************************************
*                END OF FILE
****************************************************************************/
