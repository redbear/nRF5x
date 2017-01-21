/************************************************************************//**
* @file wiring_tone.c
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
#include "wiring_tone.h"
#include "wiring_constants.h"
#include "Arduino.h"

#ifdef __cplusplus
extern "C"{
#endif

#include "app_util_platform.h"
#include "nrf_drv_gpiote.h"
#include "nrf_ppi.h"

#include "nrf_soc.h"
#include "nrf_sdm.h"

#ifdef __cplusplus
}
#endif
/****************************************************************************
*                MACRO DEFINITIONS
****************************************************************************/


/****************************************************************************
*                GLOBAL VARIABLES
****************************************************************************/


/****************************************************************************
*                LOCAL VARIABLES
****************************************************************************/

static volatile uint8_t  finish_flag;
static volatile uint32_t inter_count;

static uint8_t tone_pin;
/****************************************************************************
*                LOCAL FUNCTION PROTOTYPES
****************************************************************************/


/****************************************************************************
*                FUNCTION ACHIEVMENT
****************************************************************************/
void tone(uint8_t pin, uint16_t freq, uint32_t duration)
{
    PinName  nrf_pin;
    uint32_t error_code;

    nrf_pin = Pin_Arduino_to_nRF52(pin);
    MBED_ASSERT(nrf_pin != (PinName)NC);
    // Store pin
    tone_pin = pin;

    // Find appropriate values for PRESCALER and COMPARE registers
    uint8_t index;
    uint32_t compare;
    uint32_t prescaler;
    for (index=0; index<= 9; index++)
    {
        prescaler = index;
        compare = 16000000UL / freq;
        compare = compare >> (prescaler+1);
        compare = compare - 1;
        if ((compare >= 2) && (compare <= 65535))
            break;
    }
    // Serial.print("The prescaler : ");
    // Serial.println(prescaler, DEC);
    // Serial.print("The compare : ");
    // Serial.println(compare, DEC);

    // Check duration
    if(duration > 0) {
        finish_flag = 1;
        inter_count = 2 * freq * duration / 1000;
        if(inter_count == 0)
            inter_count = 1;
    }
    else {
        finish_flag = 0;
        inter_count = 0xFFFFFFFF;
    }
    //Serial.print("The inter_count : ");
    //Serial.println(inter_count, HEX);

    // Config GPIOTE task out
    nrf_drv_gpiote_out_config_t config = {
        .action     = NRF_GPIOTE_POLARITY_TOGGLE,
        .init_state = NRF_GPIOTE_INITIAL_VALUE_LOW,
        .task_pin   = true,
    };
    nrf_drv_gpiote_out_uninit((nrf_drv_gpiote_pin_t)nrf_pin);

    error_code = nrf_drv_gpiote_out_init((nrf_drv_gpiote_pin_t)nrf_pin, &config);
    //Serial.print("Err_code : ");
    //Serial.println(error_code, DEC);
    MBED_ASSERT(error_code == 0);
    nrf_drv_gpiote_out_task_enable((nrf_drv_gpiote_pin_t)nrf_pin);
    // Config PPI
    uint8_t  softdevice_enabled;
    error_code = sd_softdevice_is_enabled(&softdevice_enabled);
    MBED_ASSERT(error_code == 0);
    if(softdevice_enabled) {
        error_code = sd_ppi_channel_assign(TONE_USED_PPI_CHANNAL, (const volatile void *)&TONE_USED_TIMER->EVENTS_COMPARE[0], (const volatile void *)nrf_drv_gpiote_out_task_addr_get((nrf_drv_gpiote_pin_t)nrf_pin));
        MBED_ASSERT(error_code == 0);
        error_code = sd_ppi_channel_enable_set(1 << TONE_USED_PPI_CHANNAL);
        MBED_ASSERT(error_code);
    }
    else {
        nrf_ppi_channel_endpoint_setup((nrf_ppi_channel_t)TONE_USED_PPI_CHANNAL, (uint32_t)&TONE_USED_TIMER->EVENTS_COMPARE[0], (uint32_t)nrf_drv_gpiote_out_task_addr_get((nrf_drv_gpiote_pin_t)nrf_pin));
        nrf_ppi_channel_enable((nrf_ppi_channel_t)TONE_USED_PPI_CHANNAL);
    }
    // Config TIMERx
    TONE_USED_TIMER->TASKS_STOP = 1;
    TONE_USED_TIMER->TASKS_CLEAR = 1;

    TONE_USED_TIMER->MODE = TIMER_MODE_MODE_Timer;
    TONE_USED_TIMER->PRESCALER = prescaler;
    TONE_USED_TIMER->BITMODE = TIMER_BITMODE_BITMODE_16Bit;
    TONE_USED_TIMER->SHORTS = (TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos);

    TONE_USED_TIMER->CC[0] = (uint16_t)(compare);
    TONE_USED_TIMER->EVENTS_COMPARE[0] = 0;

    TONE_USED_TIMER->INTENCLR = 0xFFFFFFFF;
    TONE_USED_TIMER->INTENSET = (TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos);
    // Enable IRQn
    NVIC_SetPriority(TONE_USED_TIMER_IRQn, APP_IRQ_PRIORITY_LOW);
    NVIC_ClearPendingIRQ(TONE_USED_TIMER_IRQn);
    NVIC_EnableIRQ(TONE_USED_TIMER_IRQn);
    // Start TIMER
    TONE_USED_TIMER->TASKS_START = 1;
}

void tone(uint8_t pin, uint16_t freq)
{
    tone(pin, freq, 0);
}

void noTone(uint8_t pin)
{
    PinName nrf_pin;

    if(pin != tone_pin)
        return;

    nrf_pin = Pin_Arduino_to_nRF52(pin);
    MBED_ASSERT(nrf_pin != (PinName)NC);

    // Stop TIMERx
    TONE_USED_TIMER->TASKS_STOP = 1;
    NVIC_DisableIRQ(TONE_USED_TIMER_IRQn);
    // Uninit PPI
    uint8_t  softdevice_enabled;
    uint32_t error_code;
    error_code = sd_softdevice_is_enabled(&softdevice_enabled);
    MBED_ASSERT(error_code == 0);
    if(softdevice_enabled) {
        error_code = sd_ppi_channel_enable_clr(1 << TONE_USED_PPI_CHANNAL);
        MBED_ASSERT(error_code == 0);
    }
    else {
        nrf_ppi_channel_disable((nrf_ppi_channel_t)TONE_USED_PPI_CHANNAL);
    }
    // Uninit GPIOTE
    nrf_drv_gpiote_out_task_disable((nrf_drv_gpiote_pin_t)nrf_pin);
    nrf_drv_gpiote_out_uninit((nrf_drv_gpiote_pin_t)nrf_pin);
    // Clear variables
    tone_pin    = 0xFF;
    finish_flag = 0;
    inter_count = 0;
}

#ifdef __cplusplus
extern "C"{
#endif

void TONE_USED_TIMER_IRQHandler(void)
{
    TONE_USED_TIMER->EVENTS_COMPARE[0] = 0;
    if(finish_flag == 1) {
        if(inter_count)
            inter_count--;
        else
            noTone(tone_pin);
    }
}

#ifdef __cplusplus
}
#endif

/****************************************************************************
*                END OF FILE
****************************************************************************/
