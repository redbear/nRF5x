/************************************************************************//**
* @file wiring_digital.h
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

#ifndef WIRING_DIGITAL_H_
#define WIRING_DIGITAL_H_

/****************************************************************************
*                HEADER FILES
****************************************************************************/


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
 * @brief Set pin mode.
 *
 * @param[in] pin
 * @param[in] mode  Pin mode:INPUT,OUTPUT,INPUT_PULLUP,INPUT_PULLDOWN.
 */
void pinMode(uint8_t pin, uint8_t mode);

/**
 * @brief Write digital pin.
 *
 * @param[in] pin
 * @param[in] value Pin status:HIGH or LOW.
 */
void digitalWrite(uint8_t pin, uint32_t value);

/**
 * @brief Read digital pin.
 *
 * @param[in] pin
 *
 * @return  Pin status:HIGH or LOW. If -1, pin error.
 */
uint8_t digitalRead(uint8_t pin);

#endif
/****************************************************************************
*                END OF FILE
****************************************************************************/
