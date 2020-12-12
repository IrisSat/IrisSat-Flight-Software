#ifndef INCLUDE_CAN_H_
#define INCLUDE_CAN_H_
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// License:
//  Available under MIT license.
//
// Repository:
//  Github: https://github.com/UMSATS/cdh-tsat5
//
// File Description:
//  Functions for CAN initialization, message reception, and message transmission. Received messages are read into a Queue, which
//  can be handled by a dedicated task.
//
// History
// 2019-03-28 by Tamkin Rahman
// - Created.
//	2020-04-29 by Joseph Howarth
//	- Changed CANMessage_t to remove extended identifier since all messages are extended.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <FreeRTOS/FreeRTOS-Source/include/FreeRTOS.h>
#include <FreeRTOS/FreeRTOS-Source/include/queue.h>
#include "drivers/mss_can/mss_can.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define MAX_CAN_DATA_LENGTH 8

// Use this macro to determine whether the driver is ready to send a CAN message.
#define CAN_TRANSMIT_READY() (CAN_OK == MSS_CAN_send_message_ready(&g_can0))

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTS AND STRUCT TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
    uint32_t id;                         // Message ID.
    uint8_t  dlc;                        // Data length code (i.e. number of bytes).

	/**< Frame Data - 0 to 8 bytes */
	union __attribute__((aligned(8))) {
		uint8_t data[8];
		uint16_t data16[4];
		uint32_t data32[2];
	};
} CANMessage_t;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ENUMS AND ENUM TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// NOTE: These baud rates assume a PCLK1 of 32 MHz.
typedef enum
{
    CAN_BAUD_RATE_250K  = CAN_SPEED_32M_250K,
	CAN_BAUD_RATE_500K  = CAN_SPEED_32M_500K,
	CAN_BAUD_RATE_1000K = CAN_SPEED_32M_1M,
} CANBaudRate;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// GLOBALS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
extern QueueHandle_t can_rx_queue; // Global queue containing received CAN messages.
extern QueueHandle_t  csp_rx_queue; // Global queue containing received CAN messages, for CSP.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Initialize CAN and the rx queues. Other CAN functions or macros shouldn't be used until this function has been called.
//
// Returns:
//  1 on success, 0 on failure.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int init_CAN(
        CANBaudRate baudrate,  // The CAN bus baud rate to use.
		QueueHandle_t *csp_rx_queue_handle
        );

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Transmit a CAN message.
//
// Returns:
//  1 on success, 0 on failure.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int CAN_transmit_message(
		CANMessage_t * message  // Pointer to the CAN message object to send.
        );

#endif /* INCLUDE_CAN_H_ */
