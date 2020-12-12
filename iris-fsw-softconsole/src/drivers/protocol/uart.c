//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// License:
// 	Available under MIT license.
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
#include <FreeRTOS/FreeRTOS-Source/include/FreeRTOS.h>
#include <FreeRTOS/FreeRTOS-Source/include/queue.h>
#include <FreeRTOS/FreeRTOS-Source/include/semphr.h>
#include <FreeRTOS/FreeRTOS-Source/include/task.h>

/* Library includes. */
#include "drivers/mss_uart/mss_uart.h"
#include <firmware/CMSIS/system_m2sxxx.h>
#include <string.h>
#include <stdlib.h>

/* Application includes. */
#include "drivers/protocol/uart.h"
#include "version.h"
#include "drivers/software_update_driver.h"

#define UART_BUFFER_SIZE	256
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
				memcpy(copied_buffer, my_buffer, *uxUnreadBytes);
				uxBytesRead = *uxUnreadBytes;
//				/* Subtract the number of bytes processed from the available bytes */
				*uxUnreadBytes -= *uxUnreadBytes;
			}
			taskEXIT_CRITICAL();
		}



		/* Echo back all data to the terminal */
		prvUARTSend(&g_mss_uart0, (const uint8_t *) copied_buffer, uxBytesRead);

		/* Do any special processing based on the origin on the data */
		if(my_uart == &g_mss_uart0)
		{
			prvProcessUART0(copied_buffer, uxBytesRead);
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
	static uint16_t pos = 0;
	uint8_t i;
	static uint8_t mode = 0;
	static uint32_t numBytes = 0;
	static uint8_t image_select = 0;
	if(mode == 0){

		/* Add characters onto the command string */
		memcpy(&ucCommandString[pos], pcBuffer, ulNumBytes);
		pos += ulNumBytes;

		if(ucCommandString[pos-1] == 10)
		{
			/* End of line has been received. Send to module */
			if (xSemaphoreTake(xUARTMutex, portMAX_DELAY) == pdTRUE)
			{
				if(ucCommandString[0] == 'u'){
					if(ucCommandString[1] == '1') image_select = 1;
					else if(ucCommandString[1] == '0') image_select = 0;
					mode = 1;
				}
				else if(ucCommandString[0] == 'd'){

					if(ucCommandString[1] == '1') image_select = 1;
					else if(ucCommandString[1] == '0') image_select = 0;
					repeat_program(image_select);
				}
				else if(ucCommandString[0] == 'v'){

					if(ucCommandString[1] == '1') image_select = 1;
					else if(ucCommandString[1] == '0') image_select = 0;
					//Verify
					authenticate_firmware(image_select);
				}
				else if(ucCommandString[0] == 'p'){
					if(ucCommandString[1] == '1') image_select = 1;
					else if(ucCommandString[1] == '0') image_select = 0;
					initiate_firmware_update(image_select);
				}
				else if(ucCommandString[0] == 'a'){
					prvUARTSend(&g_mss_uart0, "MBSAT FSW V0.8.0", strlen("MBSAT FSW V0.8.0"));
				}
				else if(ucCommandString[0] == 'b'){
					 char str[25];
					 size_t freemem = xPortGetFreeHeapSize();
					 sprintf(str,"free mem: %d\n",freemem);
					 prvUARTSend(&g_mss_uart0, str, strlen(str));
				}
				pos = 0;
				memset(ucCommandString,0,UART_BUFFER_SIZE);
				xSemaphoreGive(xUARTMutex);
			}

		}
	}
	else if(mode == 1){
		/* Add characters onto the command string */
		memcpy(&ucCommandString[pos], pcBuffer, ulNumBytes);
		pos += ulNumBytes;
		if(ucCommandString[pos-1] == 10)
		{
			numBytes = (uint32_t) strtol(ucCommandString,&ucCommandString[pos-1],10); //Should check cast.
			set_program_size(numBytes,image_select);
			mode = 2;
			memset(ucCommandString,0,UART_BUFFER_SIZE);
			pos = 0;
		}
	}
	else if (mode == 2){

		if(pos + ulNumBytes > UART_BUFFER_SIZE){

			uint32_t remaining =  UART_BUFFER_SIZE-pos;
			//Fill up current buffer.
			memcpy(&ucCommandString[pos], pcBuffer,remaining);
			pos += remaining;

			//Save the current buffer.
			save_program(ucCommandString, pos,image_select);
			numBytes -= pos;
			//Reset buffer and copy overflow data.
			pos = 0;
			memcpy(&ucCommandString[pos], &pcBuffer[remaining], ulNumBytes-(remaining));
			pos += ulNumBytes-(remaining) ;

		}
		else if(pos + ulNumBytes == UART_BUFFER_SIZE){
			//Copy the data and then write to flash.
			memcpy(&ucCommandString[pos], pcBuffer, ulNumBytes);
			pos += ulNumBytes;

			save_program(ucCommandString, pos,image_select);
			numBytes -= pos;
			//Reset index in buffer to refill from the beginning.
			pos = 0;
		}
		else{
			//Just copy the data and wait for a full buffer.
			memcpy(&ucCommandString[pos], pcBuffer, ulNumBytes);
			pos += ulNumBytes;

			//Handle the last bytes transfered when there is less than 256 left.
			if(numBytes<UART_BUFFER_SIZE){
				save_program(ucCommandString, pos,image_select);
				numBytes -= pos;
				//Reset index in buffer to refill from the beginning.
				pos = 0;
			}
		}
		if(numBytes <= 0){
			mode = 0;
			prvUARTSend(&g_mss_uart0, "Done uploading program!\n", strlen("Done uploading program!\n"));
		}
	}
}


 void prvUARTSend(mss_uart_instance_t *pxUART, const uint8_t *pcBuffer, size_t xBufferLength)
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
