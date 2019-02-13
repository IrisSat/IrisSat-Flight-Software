//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// License:
// 	Available under the GNU General Public License v3.0 (GPL-3.0-or-later)
//
// Repository:
//  Github: https://github.com/UMSATS/cdh-tsat5
//
// File Description:
//  UART tasks and functions for the project. Created using the demo project given as a starting point:
//	- https://www.digikey.com/eewiki/display/microcontroller/Getting+Started+with+the+Microsemi+SmartFusion+2+Maker-Board
//
// History
// 2019-01-16 by Tamkin Rahman and Joseph Howarth
// - Removed UART1 and IoT node code.
// 2019-02-08 by Tamkin Rahman
// - Print the version string on request as well.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 * uart.c
 *
 *  Created on: Oct 26, 2017
 *      Author: Taylor
 */

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Library includes. */
#include "drivers/mss_uart/mss_uart.h"
#include "CMSIS/system_m2sxxx.h"
#include <string.h>
#include <stdlib.h>

/* Application includes. */
#include "uart.h"
#include "version.h"

#define UART_BUFFER_SIZE	128
#define REPLY_QUEUE_SIZE	5

static const IRQn_Type xUART0_IRQ = UART0_IRQn;
static uint8_t uart0buffer[UART_BUFFER_SIZE];
static uint8_t copied_buffer[UART_BUFFER_SIZE];
static size_t uxUART0UnreadBytes;

TaskHandle_t xUART0RxTaskToNotify;
SemaphoreHandle_t xUARTMutex;
QueueHandle_t xReplyQueue;

void vInitializeUARTs(uint32_t ulBaud0)
{
	/* Initialize UART 0 */
	MSS_UART_init(&g_mss_uart0,
					ulBaud0,
					MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);

	/* Create a mutex that will allow the UART to be accessed by multiple tasks
	 * Most likely will not be necessary, but just in case */
	xUARTMutex = xSemaphoreCreateMutex();

	/* Create a queue to notify the upload task of replies from the module */
	xReplyQueue = xQueueCreate(REPLY_QUEUE_SIZE, sizeof(uint32_t));

	/* The interrupt handler makes use of FreeRTOS API functions, so its
	priority must be at or below the configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
	setting (the higher the numeric priority, the lower the logical priority). */
	NVIC_SetPriority( xUART0_IRQ, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY );

	/* Set the UART Rx notification function to trigger after a single byte is received. */
	MSS_UART_set_rx_handler(&g_mss_uart0, prvUARTRxNotificationHandler, MSS_UART_FIFO_SINGLE_BYTE );
}

void vTaskUARTBridge(void *pvParameters)
{
	uint32_t ulNumRecvBytes;
	uint8_t ucUARTByte;
	BaseType_t xResult;
	const mss_uart_instance_t *my_uart = (mss_uart_instance_t *) pvParameters;
	const uint8_t *my_buffer = uart0buffer;
	size_t *uxUnreadBytes = &uxUART0UnreadBytes;

	size_t uxBytesRead;

	for( ;; )
	{
		/* Check if data has been received
		 * Block indefinitely until it has */
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		/* Copy data before it can be overwritten */
		if(*uxUnreadBytes > 0)
		{
			taskENTER_CRITICAL();
			{
				strlcpy(copied_buffer, my_buffer, *uxUnreadBytes + 1);

				/* Subtract the number of bytes processed from the available bytes */
				*uxUnreadBytes -= *uxUnreadBytes;
			}
			taskEXIT_CRITICAL();
		}

		uxBytesRead = strlen(copied_buffer);
		for (int ix = 0; ix < uxBytesRead; ix++)
		{
			if (copied_buffer[ix] == 'v')
			{
				prvUARTSend(&g_mss_uart0, (const uint8_t *) CDH_SW_VERSION_STRING, strlen(CDH_SW_VERSION_STRING));
				break;
			}
		}
		/* Echo back all data to the terminal */
		prvUARTSend(&g_mss_uart0, (const uint8_t *) copied_buffer, strlen(copied_buffer));

		/* Do any special processing based on the origin on the data */
		if(my_uart == &g_mss_uart0)
		{
			prvProcessUART0(copied_buffer, strlen(copied_buffer));
		}
	}
}



static void prvUARTRxNotificationHandler( mss_uart_instance_t *pxUART )
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	TaskHandle_t xTaskToNotify = xUART0RxTaskToNotify;
	uint8_t *target_buffer = uart0buffer ;

	size_t uxNumBytesRecvd;
	size_t *uxUnreadBytes = &uxUART0UnreadBytes ;

	/* Read the UART's FIFO */
	uxNumBytesRecvd = MSS_UART_get_rx(pxUART, target_buffer + *uxUnreadBytes, sizeof(target_buffer));
	if( uxNumBytesRecvd )
	{
		/* Increment the number of unread bytes available */
		*uxUnreadBytes += uxNumBytesRecvd;

		/* Notify the receiving task */
		vTaskNotifyGiveFromISR(xTaskToNotify, &xHigherPriorityTaskWoken);

		/* portEND_SWITCHING_ISR() or portYIELD_FROM_ISR() can be used here. */
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
}

static void prvProcessUART0(uint8_t *pcBuffer, uint32_t ulNumBytes)
{
	/* Actions to be taken with data received from UART 0
	 * Keep track of the characters added through the terminal */

	/* String to contain the entire command to be sent to the ESP8266 module */
	static uint8_t ucCommandString[UART_BUFFER_SIZE];
	static uint8_t pos = 0;
	uint8_t i;

	/* Add characters onto the command string */
	memcpy(&ucCommandString[pos], pcBuffer, ulNumBytes);
	pos += ulNumBytes;

	if(ucCommandString[pos-1] == 10)
	{
		/* End of line has been received. Send to module */
		if (xSemaphoreTake(xUARTMutex, portMAX_DELAY) == pdTRUE)
		{
			prvUARTSend(&g_mss_uart0, "test\n\r", strlen("test\n\r"));
			xSemaphoreGive(xUARTMutex);
		}
		pos = 0;
	}
}


static void prvUARTSend(mss_uart_instance_t *pxUART, const uint8_t *pcBuffer, size_t xBufferLength)
{
	const TickType_t xVeryShortDelay = 2UL;

	if(xBufferLength > 0)
	{
		MSS_UART_irq_tx( (mss_uart_instance_t *) pxUART, pcBuffer, xBufferLength );

		/* Ensure any previous transmissions have completed.  The default UART
		interrupt does not provide an event based method of	signally the end of a Tx
		- this is therefore a crude poll of the Tx end status.  Replacing the
		default UART handler with one that 'gives' a semaphore when the Tx is
		complete would allow this poll loop to be replaced by a simple semaphore
		block. */
		while( MSS_UART_tx_complete( ( mss_uart_instance_t * ) pxUART ) == pdFALSE )
		{
			vTaskDelay( xVeryShortDelay );
		}
	}
}

