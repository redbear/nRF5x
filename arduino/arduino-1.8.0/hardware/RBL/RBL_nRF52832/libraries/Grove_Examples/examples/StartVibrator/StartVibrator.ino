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
 * Example - 04: Start a vibrator
 */
 
// name the pins
#define BUTTONPIN D2
#define MOTORPIN D0

// This routine runs only once upon reset
void setup() {
  pinMode(BUTTONPIN, INPUT);                            
  pinMode(MOTORPIN, OUTPUT);                          
}

// This routine loops forever
void loop() {
  int val = digitalRead(BUTTONPIN);              // read the hall sensor pin

  if (val == 0)                                  // if magnet detected
    digitalWrite(MOTORPIN, LOW);                 // let the motor vibrate
  else
    digitalWrite(MOTORPIN, HIGH);                // stop it
    
  delay(50);
}

