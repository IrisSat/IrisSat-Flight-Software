//------------------------------------------------------------------------------
// MBSat-1
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
#include "tasks/csp_server.h"
#include "tasks/telemetry.h"

#include "csp/csp.h"
#include "csp/interfaces/csp_if_can.h"
#include "csp/interfaces/csp_if_kiss.h"
#include "drivers/uart_driver_csp.h"

#include "FreeRTOS.h"
#include "queue.h"



//------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//  Description: This function configures CSP. It handles setting up buffers,
//               initializing the interface(s), setting up the router table,
//               and starting the router task. The defualt values are listed
//               in the header file.
//
// Returns:     Returns 1 if sucessful, 0 if there is an error.
//------------------------------------------------------------------------------
uint8_t configure_csp();

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

void vCSP_Server(void * pvParameters){

    InputQueues_t * queues = (InputQueues_t *) pvParameters;

    uint8_t result = configure_csp();

    csp_conn_t * conn = NULL;
	csp_packet_t * packet= NULL;
	csp_socket_t * socket = csp_socket(0);

    //Listen for messages to all ports.
    csp_bind(socket, CSP_ANY);

    //Have up to 4 backlog connections.
    csp_listen(socket,4);

    //TODO: Check return of csp_bind and listen, then handle errors.
    while(1) {

		conn = csp_accept(socket, 1000);

		if(conn){

			packet = csp_read(conn,0);

            #ifdef DEBUG
                //prvUARTSend(&g_mss_uart0, packet->data, packet->length);
			#endif

            //Handle the message based on the port it was sent to.
            int dest_port = csp_conn_dst(conn);

            switch(dest_port){

                CSP_COMMAND_PORT:
                    xQueueSendToBack(queues->command_queue,packet->data,100);
                    break;

                CSP_DATA_PORT:
                    xQueueSendToBack(queues->data_queue,packet->data,100);
                    break;

                default:
                    csp_service_handler(conn,packet);
                    break;
            }
            //Should buffer free be here? Example doesn't call this after csp_service handler.
            csp_buffer_free(packet);
			csp_close(conn);
		}
	}
}

uint8_t configure_csp(){

    uint8_t result = 1; //Sucess
    // CAN parameters are not actually used. Need to decide where we are doing
    // CAN init. Right now the csp driver does this, but uses hard coded params.
    struct csp_can_config can_conf;
    can_conf.bitrate=250000;
    can_conf.clock_speed=250000;
    can_conf.ifc = "CAN";

    /* Init buffer system with 5 packets of maximum 256 bytes each */
    int status = csp_buffer_init(CSP_DEFAULT_NUM_BUFFERS, CSP_DEFAULT_SIZE_BUFFER);
    if(status != CSP_ERR_NONE){
        result = 0;
        return result;
    }
    /* Init CSP with address 0 */
    status = csp_init(CDH_CSP_ADDRESS);
    if(status != CSP_ERR_NONE){
        result = 0;
        return result;
    }

    /* Init the CAN interface with hardware filtering */
    status = csp_can_init(CSP_CAN_MASKED, &can_conf);
    if(status != CSP_ERR_NONE){
        result = 0;
        return result;
    }

    csp_kiss_init(&uartInterface, &uartHandle, uartPutChar, NULL, "KISS");

    /* Setup default route to CAN interface */
    //status = csp_rtable_set(CSP_DEFAULT_ROUTE,0, &csp_if_can,CSP_NODE_MAC);
    char* canRoute = "0/2 CAN";
    char* gndRoute = "9/5 KISS";

   csp_rtable_load(canRoute);
   csp_rtable_load(gndRoute);
    if(status != CSP_ERR_NONE){
        result = 0;
        return result;
    }

    /* Start router task with 100 word stack, OS task priority 1 */
    status = csp_route_start_task(4*CSP_DEFAULT_ROUTER_STACK_SIZE, CSP_DEFAULT_ROUTER_PRIORITY);
    if(status != CSP_ERR_NONE){
        result = 0;
        return result;
    }

    return result;
}
