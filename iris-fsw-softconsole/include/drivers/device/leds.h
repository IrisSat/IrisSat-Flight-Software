#ifndef RTOSDEMO_LEDS_H_
#define RTOSDEMO_LEDS_H_
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  LED tasks and functions for the project. Created using the demo project given as a starting point:
//	- https://www.digikey.com/eewiki/display/microcontroller/Getting+Started+with+the+Microsemi+SmartFusion+2+Maker-Board
//
// History
// 2019-01-16 by Tamkin Rahman and Joseph Howarth
// - Removed UART1 and IoT node code.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 * leds.h
 *
 *  Created on: Oct 25, 2017
 *      Author: Taylor
 */

void vInitializeLEDs( void );
void vSetLED( UBaseType_t uxLED, BaseType_t xValue );
void vToggleLED( UBaseType_t uxLED );
void vTaskSpinLEDs(void *pvParameters);

#endif /* RTOSDEMO_LEDS_H_ */
