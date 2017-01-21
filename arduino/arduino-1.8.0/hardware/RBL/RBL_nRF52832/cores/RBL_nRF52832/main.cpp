
#define ARDUINO_MAIN

#include "Arduino.h"

/*
 * \brief Main entry point of Arduino application
 */


int __attribute__ ((weak)) main(void)
{
    setup();

    for (;;)
    {
        loop();
    }

    return 0;
}
