#ifndef RTOSDEMO_INCLUDE_UART_H_
#define RTOSDEMO_INCLUDE_UART_H_
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  UART tasks and functions for the project. Created using the demo project given as a starting point:
//	- https://www.digikey.com/eewiki/display/microcontroller/Getting+Started+with+the+Microsemi+SmartFusion+2+Maker-Board
//
// History
// 2019-01-16 by Tamkin Rahman and Joseph Howarth
// - Removed UART1 and IoT node code.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 * uart.h
 *
 *  Created on: Oct 26, 2017
 *      Author: Taylor
 */

void vInitializeUARTs(uint32_t baud0);
void vTaskUARTBridge(void *pvParameters);
static void prvUARTRxNotificationHandler( mss_uart_instance_t *pxUART );
static void prvProcessUART0(uint8_t *pcBuffer, uint32_t ulNumBytes);
 void prvUARTSend(mss_uart_instance_t *pxUART, const uint8_t *pcBuffer, size_t xBufferLength);

#endif /* RTOSDEMO_INCLUDE_UART_H_ */
