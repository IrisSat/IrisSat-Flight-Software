//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// License:
//     Available under the GNU General Public License v3.0 (GPL-3.0-or-later)
//
// Repository:
//  Github: https://github.com/UMSATS/cdh-tsat5
//
// File Description:
//  LED tasks and functions for the project. Created using the demo project given as a starting point:
//    - https://www.digikey.com/eewiki/display/microcontroller/Getting+Started+with+the+Microsemi+SmartFusion+2+Maker-Board
//
// History
// 2019-01-16 by Tamkin Rahman and Joseph Howarth
// - Removed UART1 and IoT node code.
// 2019-04-16 by Tamkin Rahman
// - On startup, leave on LED0 and LED1 for 2 seconds (to make it easy to see whether a reset occurred).
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 * leds.c
 *
 *  Created on: Oct 25, 2017
 *      Author: Taylor
 */

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Library includes. */
#include "drivers/mss_gpio/mss_gpio.h"
#include "CMSIS/system_m2sxxx.h"

/* Application includes. */
#include "leds.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define boardNUM_LEDS    8

// Note that LED's are active low.
#define LED_ON            pdFALSE
#define LED_OFF            pdTRUE

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/* Remember the state of the outputs for easy toggling. */
static unsigned char ucPortState = 0;
/* MSS GPIOs */
static const mss_gpio_id_t ucLEDs[ boardNUM_LEDS ] = { MSS_GPIO_0, MSS_GPIO_1, MSS_GPIO_2, MSS_GPIO_3,
                                                    MSS_GPIO_4, MSS_GPIO_5, MSS_GPIO_6, MSS_GPIO_7 };

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void vInitializeLEDs(void)
{
    int x;

    /* Ensure the LEDs are outputs and HIGH (OFF) to start. */
    for( x = 0; x < boardNUM_LEDS; x++ )
    {
        MSS_GPIO_config( ucLEDs[ x ], MSS_GPIO_OUTPUT_MODE );
        vSetLED( x, pdTRUE );
    }
}

void vSetLED(unsigned portBASE_TYPE uxLED, signed portBASE_TYPE xValue)
{
    if( uxLED < boardNUM_LEDS )
    {
        taskENTER_CRITICAL();
        {
            MSS_GPIO_set_output( ucLEDs[ uxLED ], xValue );

            /* Remember the new output state. */
            if( xValue == 0 )
            {
                ucPortState &= ~( 1 << uxLED );
            }
            else
            {
                ucPortState |= ( 1 << uxLED );
            }
        }
        taskEXIT_CRITICAL();
    }
}

void vToggleLED(unsigned portBASE_TYPE uxLED)
{
    if( uxLED < boardNUM_LEDS )
    {
        taskENTER_CRITICAL();
        {
            vSetLED( uxLED, !( ucPortState & ( 1 << uxLED ) ) );
        }
        taskEXIT_CRITICAL();
    }
}

void vTaskSpinLEDs(void *pvParameters)
{
    /* Create a spinning effect with the LEDs */
    static unsigned char ucLEDPos = 1;
    static signed char direction = 1;
    const TickType_t xDelay85ms = pdMS_TO_TICKS(85);

    // Leave 2 LED's on for 2 seconds on startup.
    taskENTER_CRITICAL();
    {
        vSetLED(0, LED_ON);
        vSetLED(1, LED_ON);
    }
    taskEXIT_CRITICAL();

    vTaskDelay(pdMS_TO_TICKS(2000));

    for( ;; )
    {
        if( ucLEDPos == boardNUM_LEDS - 1 || ucLEDPos == 0)
        {
            // Change direction
            direction *= -1;

            taskENTER_CRITICAL();
            {
                // Turn on current LED
                vSetLED(ucLEDPos, LED_ON);
                // Turn off last LED
                vSetLED(ucLEDPos+direction, LED_OFF);
            }
            taskEXIT_CRITICAL();

            // Increment position
            ucLEDPos+= direction;
        }
        else
        {
            taskENTER_CRITICAL();
            {
                // Turn off last LED
                vSetLED(ucLEDPos-direction, LED_OFF);
                // Turn on current LED
                vSetLED(ucLEDPos, LED_ON);
            }
            taskEXIT_CRITICAL();

            // Increment position
            ucLEDPos+= direction;
        }

        vTaskDelay(xDelay85ms);
    }
}
