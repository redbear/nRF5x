/************************************************************************//**
* @file pin_transform.h
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

#ifndef PIN_TRANSFORM_H_
#define PIN_TRANSFORM_H_

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
 * @brief Pin mapping
 *
 * @param[in] pin   Arduino pin
 *
 * @return nRF52 pin
 */
PinName Pin_Arduino_to_nRF52(uint8_t pin);

#endif
/****************************************************************************
*                END OF FILE
****************************************************************************/
