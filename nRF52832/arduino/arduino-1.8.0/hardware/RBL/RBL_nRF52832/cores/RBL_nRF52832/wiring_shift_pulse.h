/************************************************************************//**
* @file wiring_shift_pulse.h
*
* @version 1.0.0
*
* @author RedBearLab
*
* @date 2016/11/10
*
* @brief Debug APIs declaration
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

#ifndef WIRING_SHIFT_PULSE_H_
#define WIRING_SHIFT_PULSE_H_

/****************************************************************************
*                HEADER FILES
****************************************************************************/
#include <stdint.h>

/****************************************************************************
*                MACRO DEFINITIONS
****************************************************************************/


/****************************************************************************
*                TYPE DEFINITIONS
****************************************************************************/


/****************************************************************************
*                GLOABLE FUNCTION DECLARATION
****************************************************************************/
/**
 * @brief Shift in a data
 *
 * @param[in] dataPin
 * @param[in] clockPin
 * @param[in] bitOrder    LSBFIRST or MSBFIRST
 */
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, BitOrder bitOrder);

/**
 * @brief Shift out a data
 *
 * @param[in] dataPin
 * @param[in] clockPin
 * @param[in] bitOrder    LSBFIRST or MSBFIRST
 * @param[in] value
 */
void shiftOut(uint8_t dataPin, uint8_t clockPin, BitOrder bitOrder, uint8_t value);

/**
 * @brief Read a pulse (either HIGH or LOW) on a pin
 *
 * @param[in] pin
 * @param[in] state  HIGH or LOW
 * @param[in] timeout
 *
 * @return pulse in microseconds or 0 timeout
 */
uint32_t pulseIn(uint8_t pin, uint8_t state, uint32_t timeout = 1000000L);

/**
 * @brief Read a pulse(in microseconds) (either HIGH or LOW) on a pin
 *        Works on pulses from 2-3 microseconds to 3 minutes in length,
 *        But must be called at least a few dozen microseconds before the start of the pulse.
 *
 *        This function relies on micros() so cannot be used in noInterrupt() context
 *
 * @param[in] pin
 * @param[in] state  HIGH or LOW
 * @param[in] timeout
 *
 * @return pulse in microseconds or 0 timeout
 */
uint32_t pulseInLong(uint8_t pin, uint8_t state, uint32_t timeout = 1000000L);

#endif
/****************************************************************************
*                END OF FILE
****************************************************************************/
