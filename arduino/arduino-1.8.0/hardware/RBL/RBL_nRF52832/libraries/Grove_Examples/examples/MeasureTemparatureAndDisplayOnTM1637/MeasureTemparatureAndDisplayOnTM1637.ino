/*
 * Copyright (c) 2017 RedBear
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 */

/*
 * Example - 05: Measure temparature and display it on TM1637
 */
/*
 * THIS DEMO ONLY WORK FOR BLEND2
 */
 
 
#include "Arduino.h"
#include <math.h>
#include "TM1637.h"

void dispNum(unsigned int num);

// name the pins
#define CLK D2
#define DIO D3
#define TEMPPIN A0

TM1637 tm1637(CLK,DIO);

// This routine runs only once upon reset
void setup() {
  tm1637.set();                                 // cofig TM1637
  tm1637.init();                                // clear the display
  Serial.begin(9600);                           // init serial port on USB interface
}

// This routine loops forever
void loop() {
  int B = 3975;                                 // B value of the thermistor

  int analogValue = analogRead(TEMPPIN);        // read rotary pin
  float resistance = (float)(1023 - analogValue) * 10000 / analogValue;   //get the resistance of the sensor
  float temperature = 1 / (log(resistance/10000) / B + 1 / 298.15) - 273.15;  //convert to temperature via datasheet
  Serial.print("analogValue: ");
  Serial.println(analogValue);
  Serial.print("resistance: ");
  Serial.println(resistance);
  Serial.print("temperature: ");
  Serial.println(temperature);
  Serial.println("");
  dispNum((unsigned int)(temperature + 0.5));  // display the voltage
  delay(200);
}

// display a integer value less then 10000
void dispNum(unsigned int num) {
  int8_t TimeDisp[] = { 0x01,0x02,0x03,0x04 };    // limit the maximum number

  if (num > 9999) num = 9999;
  TimeDisp[0] = num / 1000;
  TimeDisp[1] = num % 1000 / 100;
  TimeDisp[2] = num % 100 / 10;
  TimeDisp[3] = num % 10;
  tm1637.display(TimeDisp);
}

