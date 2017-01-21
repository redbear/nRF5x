/*
 * MMA7760.h
 * Library for accelerometer_MMA7760
 *
 * Copyright (c) 2013 seeed technology inc.
 * Author        :   FrankieChu 
 * Create Time   :   Jan 2013
 * Change Log    :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 
#ifndef __MMC7660_H__
#define __MMC7660_H__


#include "Arduino.h"

#define MMA7660_ADDR  0x4c

#define MMA7660_X     0x00
#define MMA7660_Y     0x01
#define MMA7660_Z     0x02
#define MMA7660_TILT  0x03
#define MMA7660_SRST  0x04
#define MMA7660_SPCNT 0x05
#define MMA7660_INTSU 0x06
#define MMA7660_MODE  0x07
    #define MMA7660_STAND_BY 0x00
    #define MMA7660_ACTIVE   0x01   
#define MMA7660_SR    0x08      //sample rate register
    #define AUTO_SLEEP_120  0X00//120 sample per second
    #define AUTO_SLEEP_64   0X01
    #define AUTO_SLEEP_32   0X02
    #define AUTO_SLEEP_16   0X03
    #define AUTO_SLEEP_8    0X04
    #define AUTO_SLEEP_4    0X05
    #define AUTO_SLEEP_2    0X06
    #define AUTO_SLEEP_1    0X07
#define MMA7660_PDET  0x09
#define MMA7660_PD    0x0A
class MMA7660
{
private:
    void write(uint8_t _register, uint8_t _data);
    uint8_t read(uint8_t _register);
public:
    void init();
    void setMode(uint8_t mode);
    void setSampleRate(uint8_t rate);
    void getXYZ(int8_t *x,int8_t *y,int8_t *z);
    void getAcceleration(float *ax,float *ay,float *az);
};

#endif



