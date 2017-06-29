/************************************************************************//**
* @file wiring_analog.c
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
#include <math.h>
#include "Arduino.h"
#include "wiring_analog.h"

/****************************************************************************
*                MACRO DEFINITIONS
****************************************************************************/
#define PWM_MAX_NUM    3
#define PWM_PERIOD_US  100

/****************************************************************************
*                GLOBAL VARIABLES
****************************************************************************/


/****************************************************************************
*                LOCAL VARIABLES
****************************************************************************/
/**
 * @brief DMA RAM, store the ADC value
 */
static int16_t  saadc_value;
/**
 * @brief Resolution
 */
static uint8_t  readResolution  = DEFAULT_READ_RESOLUTION;
static uint8_t  writeResolution = DEFAULT_WRITE_RESOLUTION;
/**
 * @brief Reference
 */
static uint32_t saadReference   = SAADC_CH_CONFIG_REFSEL_VDD1_4;

/**
 * @brief PWM
 */
static pwmout_t pwm_instance[PWM_MAX_NUM] = { {(PWMName)0, (PinName)NC, 0, NULL},
                                              {(PWMName)0, (PinName)NC, 0, NULL},
                                              {(PWMName)0, (PinName)NC, 0, NULL} };
/****************************************************************************
*                LOCAL FUNCTION PROTOTYPES
****************************************************************************/

static uint8_t getMatchChannel(PinName pin);
static uint8_t getFreeChannel(void);
/****************************************************************************
*                FUNCTION ACHIEVMENT
****************************************************************************/
static inline uint32_t conversionResolution(uint32_t value, uint32_t from, uint32_t to)
{
    if (from == to)
        return value;
    if (from > to)
        return value >> (from-to);
    else
        return value << (to-from);
}

void analogReadResolution(uint8_t resolution)
{
    readResolution = resolution;
}

void analogWriteResolution(uint8_t resolution)
{
    writeResolution = resolution;
}

void analogReference(eAnalogReference_t type)
{
    switch(type) {
        case REFSEL_INTERNAL:
            saadReference = SAADC_CH_CONFIG_REFSEL_Internal;
            break;
        case REFSEL_VDD1_4:
            saadReference = SAADC_CH_CONFIG_REFSEL_VDD1_4;
            break;
        default:
            saadReference = SAADC_CH_CONFIG_REFSEL_VDD1_4;
            break;
    }
}

uint32_t analogRead(uint8_t pin)
{
    PinName  nrf_pin;
    uint32_t saadcResolution;
    uint32_t resolution;
    uint32_t config_gain = SAADC_CH_CONFIG_GAIN_Gain1_4;
    uint32_t pselp = SAADC_CH_PSELP_PSELP_NC;

    nrf_pin = Pin_Arduino_to_nRF52(pin);
    switch( nrf_pin ) {
        case 2  : pselp = SAADC_CH_PSELP_PSELP_AnalogInput0; break;
        case 3  : pselp = SAADC_CH_PSELP_PSELP_AnalogInput1; break;
        case 4  : pselp = SAADC_CH_PSELP_PSELP_AnalogInput2; break;
        case 5  : pselp = SAADC_CH_PSELP_PSELP_AnalogInput3; break;
        case 28 : pselp = SAADC_CH_PSELP_PSELP_AnalogInput4; break;
        case 29 : pselp = SAADC_CH_PSELP_PSELP_AnalogInput5; break;
        case 30 : pselp = SAADC_CH_PSELP_PSELP_AnalogInput6; break;
        case 31 : pselp = SAADC_CH_PSELP_PSELP_AnalogInput7; break;
        default : return 0;
    }
    //
    if(readResolution <= 8) {
        resolution = 8;
        saadcResolution = SAADC_RESOLUTION_VAL_8bit;
    }
    else if(readResolution <= 10) {
        resolution = 10;
        saadcResolution = SAADC_RESOLUTION_VAL_10bit;
    }
    else if(readResolution <= 12) {
        resolution = 12;
        saadcResolution = SAADC_RESOLUTION_VAL_12bit;
    }
    else {
        resolution = 14;
        saadcResolution = SAADC_RESOLUTION_VAL_14bit;
    }
    // Set the resolution
    NRF_SAADC->RESOLUTION  = saadcResolution;
    // Bypass oversampling
    NRF_SAADC->OVERSAMPLE  = (SAADC_OVERSAMPLE_OVERSAMPLE_Bypass << SAADC_OVERSAMPLE_OVERSAMPLE_Pos);
    // Disable all interrupts
    NRF_SAADC->INTENCLR = 0xFFFFFFFF;
    // Clear event flag
    NRF_SAADC->EVENTS_END = 0;
    NRF_SAADC->EVENTS_DONE = 0;
    // Enable NRF_SAADC.
    NRF_SAADC->ENABLE = (SAADC_ENABLE_ENABLE_Enabled << SAADC_ENABLE_ENABLE_Pos);
    for (int i = 0; i < 8; i++) {
        NRF_SAADC->CH[i].PSELN = SAADC_CH_PSELP_PSELP_NC;
        NRF_SAADC->CH[i].PSELP = SAADC_CH_PSELP_PSELP_NC;
    }
    // Input range = (+- 0.6 V or +-VDD/4)/Gain
    // RESULT = [V(P) – V(N) ] * GAIN/REFERENCE * 2^(RESOLUTION - m)
    // If CONFIG.MODE=SE,m=0 or if CONFIG.MODE=Diff,m=1.
    if(saadReference == SAADC_CH_CONFIG_REFSEL_Internal) {
        // Reference is Internal 0.6V, Input valtage is 0~3.6V
        config_gain = SAADC_CH_CONFIG_GAIN_Gain1_6;
    }
    else if(saadReference == SAADC_CH_CONFIG_REFSEL_VDD1_4) {
        // Reference is VDD, Input valtage is 0~VDD
        config_gain = SAADC_CH_CONFIG_GAIN_Gain1_4;
    }
    NRF_SAADC->CH[0].CONFIG = ( (SAADC_CH_CONFIG_RESP_Bypass << SAADC_CH_CONFIG_RESP_Pos) | //Positive channel resistor control:Bypass resistor ladder.
                                (SAADC_CH_CONFIG_RESP_Bypass << SAADC_CH_CONFIG_RESN_Pos) | //Negative channel resistor control:Bypass resistor ladder.
                                (config_gain  << SAADC_CH_CONFIG_GAIN_Pos) | //Gain control
                                (saadReference << SAADC_CH_CONFIG_REFSEL_Pos) | //Reference
                                (SAADC_CH_CONFIG_TACQ_10us << SAADC_CH_CONFIG_TACQ_Pos) | //Acquisition time:ADC uses to sample the input voltage.
                                (SAADC_CH_CONFIG_MODE_SE << SAADC_CH_CONFIG_MODE_Pos) |  //Single ended, PSELN will be ignored, negative input to ADC shorted to GND.
                                (SAADC_CH_CONFIG_BURST_Disabled << SAADC_CH_CONFIG_BURST_Pos) //Disable burst mode(normal operation).
                               );
    NRF_SAADC->CH[0].PSELN = SAADC_CH_PSELP_PSELP_NC;
    NRF_SAADC->CH[0].PSELP = pselp;
    // Set DMA RAM.
    saadc_value = 0;
    NRF_SAADC->RESULT.PTR = (uint32_t)&saadc_value;
    NRF_SAADC->RESULT.MAXCNT = 1; //Only one sample.
    // Start SAADC.
    NRF_SAADC->TASKS_START = 1;
    while(!NRF_SAADC->EVENTS_STARTED);
    NRF_SAADC->EVENTS_STARTED = 0;
    // Start sample.
    NRF_SAADC->TASKS_SAMPLE = 1;
    while(!NRF_SAADC->EVENTS_END);
    NRF_SAADC->EVENTS_END = 0;
    // Stop SAADC.
    NRF_SAADC->TASKS_STOP = 1;
    while(!NRF_SAADC->EVENTS_STOPPED);
    NRF_SAADC->EVENTS_STOPPED = 0;

    // If value < 0, set value to zero.
    if(saadc_value < 0)
        saadc_value = 0;
    // Disable SAADC.
    NRF_SAADC->ENABLE = (SAADC_ENABLE_ENABLE_Disabled << SAADC_ENABLE_ENABLE_Pos);

    return conversionResolution(saadc_value, resolution, readResolution);
}


void analogWrite(uint8_t pin, uint32_t value)
{
    uint8_t index;
    PinName nrf_pin;

    nrf_pin = Pin_Arduino_to_nRF52(pin);
    MBED_ASSERT(nrf_pin != (PinName)NC);

    // Check channel
    index = getMatchChannel(nrf_pin);
    if(index < 3) {
        // if(value == 0) {
            ////Free pwm
            // core_util_critical_section_enter();
            // pwmout_free(&pwm_instance[index]);
            // core_util_critical_section_exit();

            // pwm_instance[index].pin = (PinName)NC;

            // pinMode(pin, OUTPUT);
            // digitalWrite(pin, LOW);
            // return;
        // }

        // This pin has been attached to PWM
        uint32_t value_8bit;
        float duty;

        value_8bit = conversionResolution(value, writeResolution, 8);
        duty = (float)value_8bit / 255;
        // Update duty
        core_util_critical_section_enter();
        pwmout_write(&pwm_instance[index], duty);
        core_util_critical_section_exit();
    }
    else {
        uint8_t ch;
        // Get a free channel
        ch = getFreeChannel();
        if(ch >= 3)
            return;
        // If value=0, set pin to LOW
        // if(value == 0) {
            // pinMode(pin, OUTPUT);
            // digitalWrite(pin, LOW);
            // return;
        // }
        // Init pwm module
        core_util_critical_section_enter();
        pwmout_init(&pwm_instance[ch], nrf_pin);
        pwmout_period_us(&pwm_instance[ch], PWM_PERIOD_US);
        core_util_critical_section_exit();
        // Update duty
        uint32_t value_8bit;
        float duty;

        value_8bit = conversionResolution(value, writeResolution, 8);
        duty = (float)value_8bit / 255;

        core_util_critical_section_enter();
        pwmout_write(&pwm_instance[ch], duty);
        core_util_critical_section_exit();
    }
}

void analogFree(uint8_t pin)
{
    uint8_t index;
    PinName nrf_pin;

    nrf_pin = Pin_Arduino_to_nRF52(pin);
    MBED_ASSERT(nrf_pin != (PinName)NC);

    index = getMatchChannel(nrf_pin);
    if(index < 3) {
        //Free pwm
        core_util_critical_section_enter();
        pwmout_free(&pwm_instance[index]);
        core_util_critical_section_exit();

        pwm_instance[index].pin = (PinName)NC;

        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
}

static uint8_t getMatchChannel(PinName pin)
{
    uint8_t index;

    for(index=0; index<PWM_MAX_NUM; index++) {
        if(pwm_instance[index].pin == pin)
            return index;
    }
    return 0xFF;
}

static uint8_t getFreeChannel(void)
{
    uint8_t index;

    for(index=0; index<PWM_MAX_NUM; index++) {
        if(pwm_instance[index].pin == (PinName)NC)
            return index;
    }
    return 0xFF;
}

/****************************************************************************
*                END OF FILE
****************************************************************************/
