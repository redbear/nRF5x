/************************************************************************//**
* @file wiring_delay.cpp
*
* @version 1.0.0
*
* @author RedBearLab
*
* @date 2016/11/09
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
#include "wiring_delay.h"

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

void delayMicroseconds(uint32_t us)
{
    uint32_t start;

    start = us_ticker_read();
    while( (us_ticker_read() - start) < us ) {
        // Wait for
    }
}

void delay(uint32_t ms)
{
    delayMicroseconds(ms*1000);
}

uint32_t micros(void)
{
    return us_ticker_read();
}

uint32_t millis(void)
{
    return (us_ticker_read() / 1000);
}

/****************************************************************************
*                END OF FILE
****************************************************************************/
