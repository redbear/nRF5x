
#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// some libraries and sketches depend on this
// AVR stuff, assuming Arduino.h or WProgram.h
// automatically includes it..
#include <avr/pgmspace.h>

#include "mbed.h"

#include "wiring_constants.h"

#include "pins_arduino.h"
#include "pin_transform.h"
#include "wiring_buffer.h"
#include "wiring_delay.h"
#include "wiring_digital.h"
#include "wiring_analog.h"
#include "wiring_interrupts.h"
#include "wiring_shift_pulse.h"
#include "wiring_serial.h"
#include "wiring_tone.h"
#include "WMath.h"

#ifdef __cplusplus
extern "C"{
#endif

void yield(void);

//sketch
extern void setup( void );
extern void loop( void );

#ifdef __cplusplus
}
#endif

extern UARTClass Serial;

#endif

