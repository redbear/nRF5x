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
 * Project - 02: Temperature Alarm
 */
/*
 * THIS DEMO ONLY WORK FOR BLEND2
 */
  
#include "Arduino.h"
#include <math.h>
#include "TM1637.h"

// name the pins
#define CLK       D2
#define DIO       D3
#define TEMPPIN   A0
#define ROTARYPIN A2
#define BUZZERPIN D0

TM1637 tm1637(CLK,DIO);

int tempMesured;                                // the temperature we mesured
int tempUserSet;                                // the temperature user set
int tempThreshould;                             // the temperature threshould
int timeout = 0;                                // for display delay

void dispNum(int num);

// This routine runs only once upon reset
void setup() {
  Serial.begin(9600);                          // init serial port on USB interface
  tm1637.set();                                 // cofig TM1637
  tm1637.init();                                // clear the display
  pinMode(BUZZERPIN, OUTPUT);                   // set buzzer pin as output
}

// This routine loops forever
void loop() {
  int B = 3975;                                 // B value of the thermistor

  int tempValue = analogRead(TEMPPIN);          // read temperature adc
  float resistance = (float)(1023 - tempValue) * 10000 / tempValue;       // get the resistance of the sensor
  float temperature = 1 / (log(resistance/10000) / B + 1 / 298.15) - 273.15;  // convert to temperature via datasheet
  Serial.print("analogValue: ");
  Serial.println(tempValue);
  Serial.print("resistance: ");
  Serial.println(resistance);
  Serial.print("temperature: ");
  Serial.println(temperature);
  Serial.println("");
  tempMesured = (int)(temperature + 0.5);

  int rotaryValue = analogRead(ROTARYPIN);  // read rotary pin
  tempUserSet = (1023 - rotaryValue) * (100 + 20) / 1023 - 20;
  Serial.print("temperature threshoul user set: ");
  Serial.println(tempUserSet);

  if(tempThreshould != tempUserSet) {           // if user rotates the rotary and the tempUserSet changed
    tempThreshould = tempUserSet;               // update threshould with user set
    timeout = 2000;                             // delay 2000ms to display tempUserSet
  }

  if(timeout > 0) {                             // select which temperature to display
    dispNum(tempUserSet);
  }
  else {
    dispNum(tempMesured);
  }

  // if only temperature is higher and magnet is detected
  if(tempMesured >= tempUserSet) {
    digitalWrite(BUZZERPIN, HIGH);              // make a alert
  }
  else {
    digitalWrite(BUZZERPIN, LOW);               // stop the alert
  }


  delay(200);
  timeout -= 200;
  if(timeout < 0) timeout = 0;
}

// display a integer value less then 10000
void dispNum(int num) {
  int8_t TimeDisp[] = { 0, 0, 0, 0 };             // limit the maximum number
  int numabs;

  if(num > 9999) num = 9999;
  if(num < -999) num = -999;
  numabs = abs(num);

  TimeDisp[0] = numabs / 1000;
  TimeDisp[1] = numabs % 1000 / 100;
  TimeDisp[2] = numabs % 100 / 10;
  TimeDisp[3] = numabs % 10;

  if(num < 0)                                   // if a negative to be display
    TimeDisp[0] = 10;                           // show 'A' at the first digit

  tm1637.display(TimeDisp);
}

