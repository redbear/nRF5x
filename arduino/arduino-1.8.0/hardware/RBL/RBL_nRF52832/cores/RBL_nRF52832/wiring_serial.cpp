/************************************************************************//**
* @file wiring_serial.c
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
#include "wiring_serial.h"

/****************************************************************************
*                MACRO DEFINITIONS
****************************************************************************/


/****************************************************************************
*                GLOBAL VARIABLES
****************************************************************************/

UARTClass   Serial;

/****************************************************************************
*                LOCAL VARIABLES
****************************************************************************/

static Ring_Buffer rx_buffer;

static serial_t serial_obj;
/****************************************************************************
*                LOCAL FUNCTION PROTOTYPES
****************************************************************************/


/****************************************************************************
*                FUNCTION ACHIEVMENT
****************************************************************************/
void store(uint8_t c)
{
    rx_buffer.store(c);
}

UARTClass::UARTClass(void)
{
    rx_buffer.clear();

    serial_obj.placeholder = 0;
}

void UARTClass::attach(uart_irq_handler handler)
{
    serial_irq_handler(&serial_obj, handler, 1);
}

void UARTClass::begin(const uint32_t BaudRate )
{
    begin(BaudRate, DEFAULT_RX_PIN, DERAULT_TX_PIN);
}

void UARTClass::begin(const uint32_t BaudRate, uint32_t rx_pin, uint32_t tx_pin)
{
    PinName nrf_tx;
    PinName nrf_rx;

    nrf_tx = Pin_Arduino_to_nRF52(tx_pin);
    nrf_rx = Pin_Arduino_to_nRF52(rx_pin);
    // Init uart
    serial_init(&serial_obj, nrf_tx, nrf_rx);
    serial_baud(&serial_obj, BaudRate);
    // Disable FlowContronl
    serial_set_flow_control(&serial_obj, FlowControlNone, (PinName)NC, (PinName)NC);
    // Enable RXIrq
    // TXIrq has a error, don't use it
    serial_irq_set(&serial_obj, RxIrq, 1);
}

void UARTClass::end(void)
{
    serial_free(&serial_obj);
    //Clean buffer
    rx_buffer.clear();
}

int UARTClass::available(void)
{
    return rx_buffer.available();
}

int UARTClass::read(void)
{
    return rx_buffer.read();
}

int UARTClass::peek(void)
{
    return rx_buffer.peek();
}

void UARTClass::flush(void)
{
    while(serial_writable(&serial_obj));
}

size_t UARTClass::write(const uint8_t c)
{
    serial_putc(&serial_obj, c);

    return 1;
}

/****************************************************************************
*                END OF FILE
****************************************************************************/
