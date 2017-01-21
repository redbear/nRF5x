/************************************************************************//**
* @file pin_transform.c
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
#include "pin_transform.h"

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

PinName Pin_Arduino_to_nRF52(uint8_t pin)
{
    PinName return_pin = (PinName)NC;

#ifdef nRF52DK
    switch(pin) {
        case 0 : return_pin = P0_11;break;//D0/RX
        case 1 : return_pin = P0_12;break;//D1/TX
        case 2 : return_pin = P0_13;break;//D2/SDA0
        case 3 : return_pin = P0_14;break;//D3/SCL0
        case 4 : return_pin = P0_15;break;//D4
        case 5 : return_pin = P0_16;break;//D5
        case 6 : return_pin = P0_17;break;//D6
        case 7 : return_pin = P0_18;break;//D7

        case 8 : return_pin = P0_19;break;//D8
        case 9 : return_pin = P0_20;break;//D9
        case 10 : return_pin = P0_22;break;//D10
        case 11 : return_pin = P0_23;break;//D11
        case 12 : return_pin = P0_24;break;//D12
        case 13 : return_pin = P0_25;break;//D13/LED

        case 14 : return_pin = P0_26;break;//SDA1
        case 15 : return_pin = P0_27;break;//SCL1

        case 16 : return_pin = P0_3;break;//A0
        case 17 : return_pin = P0_4;break;//A1
        case 18 : return_pin = P0_28;break;//A2
        case 19 : return_pin = P0_29;break;//A3
        case 20 : return_pin = P0_30;break;//A4
        case 21 : return_pin = P0_31;break;//A5

        case 22 : return_pin = P0_5;break; //UART_CTS
        case 23 : return_pin = P0_6;break; //UART_TXD
        case 24 : return_pin = P0_7;break; //UART_RTS
        case 25 : return_pin = P0_8;break; //UART_RXD

        case 26 : return_pin = P0_2;break;
        case 27 : return_pin = P0_21;break;

        case 28 : return_pin = P0_9;break;
        case 29 : return_pin = P0_10;break;

        case 30 : return_pin = P0_0;break;
        case 31 : return_pin = P0_1;break;

        default : return_pin = (PinName)NC;break;
    }
#endif

#ifdef RBL_BLEND2
    switch(pin) {
        case 0 : return_pin = P0_11;break;//D0/RX
        case 1 : return_pin = P0_12;break;//D1/TX
        case 2 : return_pin = P0_13;break;//D2/SDA0
        case 3 : return_pin = P0_14;break;//D3/SCL0
        case 4 : return_pin = P0_15;break;//D4
        case 5 : return_pin = P0_16;break;//D5
        case 6 : return_pin = P0_17;break;//D6
        case 7 : return_pin = P0_18;break;//D7

        case 8 : return_pin = P0_19;break;//D8
        case 9 : return_pin = P0_20;break;//D9
        case 10 : return_pin = P0_22;break;//D10
        case 11 : return_pin = P0_23;break;//D11
        case 12 : return_pin = P0_24;break;//D12
        case 13 : return_pin = P0_25;break;//D13/LED

        case 14 : return_pin = P0_26;break;//SDA1
        case 15 : return_pin = P0_27;break;//SCL1

        case 16 : return_pin = P0_3;break;//A0
        case 17 : return_pin = P0_4;break;//A1
        case 18 : return_pin = P0_28;break;//A2
        case 19 : return_pin = P0_29;break;//A3
        case 20 : return_pin = P0_30;break;//A4
        case 21 : return_pin = P0_31;break;//A5

        case 22 : return_pin = P0_5;break; //UART_CTS
        case 23 : return_pin = P0_6;break; //UART_TXD
        case 24 : return_pin = P0_7;break; //UART_RTS
        case 25 : return_pin = P0_8;break; //UART_RXD

        case 26 : return_pin = P0_2;break;
        case 27 : return_pin = P0_21;break;

        case 28 : return_pin = P0_9;break;
        case 29 : return_pin = P0_10;break;

        case 30 : return_pin = P0_0;break;
        case 31 : return_pin = P0_1;break;

        default : return_pin = (PinName)NC;break;
    }

#endif

#ifdef BLE_NANO2
    switch(pin) {
        case 0 : return_pin = P0_30;break;    //D0/RXD
        case 1 : return_pin = P0_29;break;    //D1/TXD
        case 2 : return_pin = P0_28;break;    //D2/CTS
        case 3 : return_pin = P0_2;break;     //D3/RTS

        case 4 : return_pin = P0_5;break;     //D4
        case 5 : return_pin = P0_4;break;     //D5
        case 6 : return_pin = P0_3;break;     //D6
        case 7 : return_pin = P0_6;break;     //D7
        case 8 : return_pin = P0_7;break;     //D8
        case 9 : return_pin = P0_8;break;     //D9
        case 10 : return_pin = P0_21;break;   //D10

        case 13 : return_pin = P0_11;break;   //D13/LED

        case 14 : return_pin = P0_9;break;    //NFC1
        case 15 : return_pin = P0_10;break;   //NFC2

        default : return_pin = (PinName)NC;break;
    }
#endif

    return (return_pin);
}

/****************************************************************************
*                END OF FILE
****************************************************************************/
