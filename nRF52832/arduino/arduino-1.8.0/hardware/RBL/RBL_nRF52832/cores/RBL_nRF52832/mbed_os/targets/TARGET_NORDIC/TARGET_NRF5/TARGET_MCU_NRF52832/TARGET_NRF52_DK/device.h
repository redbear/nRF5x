// The 'features' section in 'target.json' is now used to create the device's hardware preprocessor switches.
// Check the 'features' section of the target description in 'targets.json' for more details.
/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_DEVICE_H
#define MBED_DEVICE_H

/**
 * @brief NRF_LF_SRC_XTAL  2
 *        NRF_LF_SRC_SYNTH 3 
 *        NRF_LF_SRC_RC    4
 */
#define MBED_CONF_NORDIC_NRF_LF_CLOCK_SRC 2
#define MBED_CONF_NORDIC_UART_HWFC 0
#define MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE 9600

#define DEVICE_PORTIN           1
#define DEVICE_PORTOUT          1
#define DEVICE_PORTINOUT        1

#define DEVICE_INTERRUPTIN      1

#define DEVICE_ANALOGIN         1
#define DEVICE_ANALOGOUT        0

#define DEVICE_SERIAL           1
#define DEVICE_SERIAL_ASYNCH    0

#define DEVICE_I2C              1
#define DEVICE_I2CSLAVE         0
#define DEVICE_I2C_ASYNCH       1

#define DEVICE_SPI              1
#define DEVICE_SPISLAVE         1
#define DEVICE_SPI_ASYNCH       1

#define DEVICE_CAN              0

#define DEVICE_RTC              1

#define DEVICE_ETHERNET         0

#define DEVICE_PWMOUT           1

#define DEVICE_SEMIHOST         0

#define DEVICE_LOCALFILESYSTEM  0

#define DEVICE_LOWPOWERTIMER    1

#define DEVICE_SLEEP            1

#define DEVICE_DEBUG_AWARENESS  0

#define DEVICE_STDIO_MESSAGES   0

#define DEVICE_ERROR_PATTERN    0

#include "objects.h"

#endif
