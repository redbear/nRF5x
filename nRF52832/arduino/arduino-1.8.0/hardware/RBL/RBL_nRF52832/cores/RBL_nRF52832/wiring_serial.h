/************************************************************************//**
* @file wiring_serial.h
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

#ifndef WIRING_SERIAL_H_
#define WIRING_SERIAL_H_

/****************************************************************************
*                HEADER FILES
****************************************************************************/
#include "HardwareSerial.h"

/****************************************************************************
*                MACRO DEFINITIONS
****************************************************************************/


/****************************************************************************
*                TYPE DEFINITIONS
****************************************************************************/
class UARTClass : public HardwareSerial
{
public:
    UARTClass();

    void attach(uart_irq_handler handle);
    void begin(const uint32_t BaudRate );
    void begin(const uint32_t BaudRate, uint32_t rx_pin, uint32_t tx_pin);
    void end(void);

    int available( void );
    int read( void );
    int peek( void );
    void flush( void );
    size_t write( const uint8_t c ); //just keep the format same with the virtual function

#if defined __GNUC__ /* GCC CS3 */
    using Print::write ; // pull in write(str) and write(buf, size) from Print
#elif defined __ICCARM__ /* IAR Ewarm 5.41+ */
    virtual void write( const char *str ) ;
    virtual void write( const uint8_t *buffer, size_t size ) ;
#endif
    operator bool() { return true; }; // USART always active
};

extern "C" void store(uint8_t c);

/****************************************************************************
*                GLOABLE FUNCTION DECLARATION
****************************************************************************/


#endif
/****************************************************************************
*                END OF FILE
****************************************************************************/
