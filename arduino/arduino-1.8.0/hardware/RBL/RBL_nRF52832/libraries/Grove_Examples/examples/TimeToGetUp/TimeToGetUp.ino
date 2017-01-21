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
 * Example - 06: It's time to get up
 */


// name the pins
#define LIGHTPIN   A0
#define BUZZERPIN  D2

// This routine runs only once upon reset
void setup() {
  pinMode(BUZZERPIN, OUTPUT);                   // set user key pin as input
  Serial.begin(9600);
}

// This routine loops forever
void loop() {
  int analogValue = analogRead(LIGHTPIN);       // read light sensor pin
  Serial.print("light strength: ");
  Serial.println(analogValue);
  if (analogValue > 1000)                       // if it is bright enough
    digitalWrite(BUZZERPIN, HIGH);              // let the buzzer chirp
  else
    digitalWrite(BUZZERPIN, LOW);               // stop it
    
  delay(500);
}

