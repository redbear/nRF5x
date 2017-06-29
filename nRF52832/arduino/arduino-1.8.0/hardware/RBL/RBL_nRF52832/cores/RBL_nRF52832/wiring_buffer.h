/************************************************************************//**
* @file wiring_buffer.h
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

#ifndef WIRING_BUFFER_H_
#define WIRING_BUFFER_H_

/****************************************************************************
*                HEADER FILES
****************************************************************************/
#include <string.h>
#include <stdint.h>

/****************************************************************************
*                MACRO DEFINITIONS
****************************************************************************/
#define RING_BUFFER_MAX_SIZE 64

/****************************************************************************
*                VARIABLE DEFINITIONS
****************************************************************************/

class Ring_Buffer
{
public:
    uint8_t  ring_buffer[RING_BUFFER_MAX_SIZE];
    uint16_t head;
    uint16_t tail;

public:
    /**
     * @brief Constructor
     */
    Ring_Buffer(void){
        memset(ring_buffer, 0, RING_BUFFER_MAX_SIZE);
        head = 0;
        tail = 0;
    }
    /**
     * @brief Store a char to buffer
     *        If buffer is full, will be discarded.
     */
    void     store(uint8_t c);
    /**
     * @brief Get the number of store data
     */
    uint16_t available(void);
    /**
     * @brief Read a byte
     *        If not data, return -1.
     */
    uint8_t  read(void);
    /**
     * @brief Read a byte but don't remove it from buffer
     *        If not data, return -1.
     */
    uint8_t  peek(void);
    /**
     * @brief Clear buffer
     */
    void     clear(void);
    /**
     * @brief Check whether buffer is full
     *        1 : full, 0 : not full
     */
    bool     isFull(void);
};


/****************************************************************************
*                GLOABLE FUNCTION DECLARATION
****************************************************************************/


#endif
/****************************************************************************
*                END OF FILE
****************************************************************************/
