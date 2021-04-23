/*
 * uart_driver_csp.h
 *
 *  Created on: Apr. 12, 2021
 *      Author: Joseph Howarth
 */

#ifndef INCLUDE_DRIVERS_UART_DRIVER_CSP_H_
#define INCLUDE_DRIVERS_UART_DRIVER_CSP_H_

#include "csp/interfaces/csp_if_kiss.h"

extern csp_iface_t uartInterface;

extern csp_kiss_handle_t uartHandle;

void uartPutChar(char c);

#endif /* INCLUDE_DRIVERS_UART_DRIVER_CSP_H_ */
