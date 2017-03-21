/************************************************************************//**
* @file wiring_tone.h
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

#ifndef WIRING_TONE_H_
#define WIRING_TONE_H_

/****************************************************************************
*                HEADER FILES
****************************************************************************/


/****************************************************************************
*                MACRO DEFINITIONS
****************************************************************************/

//#define TONE_USED_GPIOTE_NUM          7
#define TONE_USED_PPI_CHANNAL         0
#define TONE_USED_TIMER               NRF_TIMER2
#define TONE_USED_TIMER_IRQn          TIMER2_IRQn
#define TONE_USED_TIMER_IRQHandler    TIMER2_IRQHandler
/****************************************************************************
*                TYPE DEFINITIONS
****************************************************************************/
#include <stdint.h>

/****************************************************************************
*                GLOABLE FUNCTION DECLARATION
****************************************************************************/
/**
 * @brief Output a tone
 *
 * @param[in] pin       Pin of output tone.
 * @param[in] freq      Frequency of tone.
 * @param[in] duration  Duration in milliseconds.Duration should be greater than (1/freq)s.
 */
void tone(uint8_t pin, uint16_t freq, uint32_t duration);

/**
 * @brief Output a tone persistently.
 *
 * @param[in] pin       Pin of output tone.
 * @param[in] freq      Frequency of tone.
 */
void tone(uint8_t pin, uint16_t freq);

/**
 * @brief Stop a tone.
 *
 * @param[in] pin       Pin of output tone.
 */
void noTone(uint8_t pin);

#endif
/****************************************************************************
*                END OF FILE
****************************************************************************/
