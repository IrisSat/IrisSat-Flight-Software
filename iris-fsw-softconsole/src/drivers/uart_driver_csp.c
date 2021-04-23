/*
 * uart_driver_csp.c
 *
 *  Created on: Apr. 12, 2021
 *      Author: Joseph Howarth
 */


#include "drivers/uart_driver_csp.h"
#include "drivers/protocol/uart.h"

csp_iface_t uartInterface = {0};

csp_kiss_handle_t uartHandle = {0};

void uartPutChar(char c){

    prvUARTSend(&g_mss_uart0, &c, 1);
}
