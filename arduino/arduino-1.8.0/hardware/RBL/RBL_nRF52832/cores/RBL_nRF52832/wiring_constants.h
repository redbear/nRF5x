/************************************************************************//**
* @file wiring_constants.h
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

#ifndef WIRING_CONSTANST_H_
#define WIRING_CONSTANST_H_

/****************************************************************************
*                HEADER FILES
****************************************************************************/
#include <algorithm>

/****************************************************************************
*                MACRO DEFINITIONS
****************************************************************************/

#define VARIANT_MCK                  64000000UL

#define clockCyclesPerMicrosecond()  ( VARIANT_MCK / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )


#define INPUT           0x00
#define OUTPUT          0x01
#define INPUT_PULLUP    0x02

#define INPUT_NOPULL    0x03
#define INPUT_PULLDOWN  0x04
#define OUTPUT_S0S1     0x05
#define OUTPUT_H0S1     0x06
#define OUTPUT_S0H1     0x07
#define OUTPUT_H0H1     0x08
#define OUTPUT_D0S1     0x09
#define OUTPUT_D0H1     0x0A
#define OUTPUT_S0D1     0x0B
#define OUTPUT_H0D1     0x0C

#define LOW             0x00
#define HIGH            0x01
#define CHANGE          0x02
#define FALLING         0x03
#define RISING          0x04

#ifndef true
#define true            0x1
#endif

#ifndef false
#define false           0x0
#endif

#define PI              3.1415926535897932384626433832795
#define HALF_PI         1.5707963267948966192313216916398
#define TWO_PI          6.283185307179586476925286766559
#define DEG_TO_RAD      0.017453292519943295769236907684886
#define RAD_TO_DEG      57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#define abs(x)                  ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)                ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg)            ((deg)*DEG_TO_RAD)
#define degrees(rad)            ((rad)*RAD_TO_DEG)
#define sq(x)                   ((x)*(x))

#define lowByte(w)              ((uint8_t) ((w) & 0xff))
#define highByte(w)             ((uint8_t) ((w) >> 8))

#define bitRead(value, bit)            (((value) >> (bit)) & 0x01)
#define bitSet(value, bit)             ((value) |= (1UL << (bit)))
#define bitClear(value, bit)           ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define bit(b) (1UL << (b))

/****************************************************************************
*                TYPE DEFINITIONS
****************************************************************************/

typedef unsigned int word;
typedef uint8_t boolean;
typedef uint8_t byte;


enum BitOrder {
    LSBFIRST = 0,
    MSBFIRST = 1
};

/****************************************************************************
*                GLOABLE FUNCTION DECLARATION
****************************************************************************/


#endif
/****************************************************************************
*                END OF FILE
****************************************************************************/
