/************************************************************************//**
* @file wiring_analog.h
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

#ifndef WIRING_ANALOG_H_
#define WIRING_ANALOG_H_

/****************************************************************************
*                HEADER FILES
****************************************************************************/
#include <stdint.h>
#include <string.h>

/****************************************************************************
*                MACRO DEFINITIONS
****************************************************************************/
#define DEFAULT_READ_RESOLUTION  10
#define DEFAULT_WRITE_RESOLUTION 8

/****************************************************************************
*                TYPE DEFINITIONS
****************************************************************************/

typedef enum{
    REFSEL_INTERNAL,
    REFSEL_VDD1_4
}eAnalogReference_t;

/****************************************************************************
*                GLOABLE FUNCTION DECLARATION
****************************************************************************/
/**
 * @brief Set the resolution of analogRead return values. Default is 10 bits.
 *
 * @param[in] resolution
 */
void analogReadResolution(uint8_t resolution);

/**
 * @brief Set the resolution of analogWrite parameters. Default is 8 bits.
 *
 * @param[in] resolution
 */
void analogWriteResolution(uint8_t resolution);

/**
 * @brief Configures the reference voltage used for analog input.
 *
 * @note  Default is REFSEL_INTERNAL.
 *
 * @param[in] type
 */
void analogReference(eAnalogReference_t type);

/**
 * @brief Reads the value from the specified analog pin.
 *
 * @param[in] pin
 */
uint32_t analogRead(uint8_t pin);

/**
 * @brief Writes an analog value (PWM wave) to a pin.
 *
 * @param[in] pin
 * @param[in] value
 */
void analogWrite(uint8_t pin, uint32_t value);

/**
 * @brief Release pin from analog function
 *
 * @param[in] pin
 */
void analogFree(uint8_t pin);

#endif
/****************************************************************************
*                END OF FILE
****************************************************************************/
