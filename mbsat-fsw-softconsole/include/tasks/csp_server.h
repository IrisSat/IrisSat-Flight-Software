#ifndef CSP_SERVER_H_
#define CSP_SERVER_H_
//------------------------------------------------------------------------------
//
// Repository:
//	Github: https://github.com/joehowarth17/ManitobaSat-Flight-Software
//
// File Description:
//  This file contains the Cubesat Space Protocol server.
//
// History
// 2020-04-10 by Joseph Howarth
// - Created.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "FreeRTOS.h"
#include "queue.h"

//------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//------------------------------------------------------------------------------

//Configuration constants for CSP.
#define CSP_MY_ADDRESS                  0
#define CSP_DEFAULT_NUM_BUFFERS         5
#define CSP_DEFAULT_SIZE_BUFFER         256  //The 256 number is from the MTU of the CAN interface.
#define CSP_DEFAULT_ROUTER_STACK_SIZE   100
#define CSP_DEFAULT_ROUTER_PRIORITY     1

//------------------------------------------------------------------------------
// ENUMERATIONS AND STRUCTS
//------------------------------------------------------------------------------

// This will be used by spi reveicer, can receiver and uart revceiver(for debugging), and
// the operations task, so this should probably be in the operations.h file.
typedef struct{

    QueueHandle_t command_queue;
    QueueHandle_t data_queue;

} InputQueues_t;

//------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Description: This task receives CSP messages over the CAN bus and
//              will put the received message in the appropriate queue.
//
//  Stack Size: The task should be initialized with 160 word stack size.
//  Parameters: InputQueues_t struct.
//------------------------------------------------------------------------------
void vCSP_Server(void * pvParameters);

#endif
