/*
 * telemetry.c
 *
 *  Created on: Mar. 22, 2021
 *      Author: Joseph Howarth
 */

#include "tasks/telemetry.h"
#include <csp/csp.h>
#include "csp/interfaces/csp_if_can.h"
#include <string.h>

//Overhead for telemetry is size of timestamp + id+length.
#define TELEM_HEADER_SIZE	(sizeof(Calendar_t)+2)

uint8_t tempBuff[256]= {0};

void unpackTelemetry(uint8_t * data, telemetryPacket_t* output){

	memcpy((void*)&output->timestamp,&data[0],sizeof(Calendar_t));
	memcpy(&output->telem_id, &data[sizeof(Calendar_t)],1);
	memcpy(&output->length, &data[sizeof(Calendar_t)+1],1);
	memcpy(tempBuff,&data[sizeof(Calendar_t)+2],output->length);
	output->data = tempBuff;
	//TODO: Implment some sort of control for sharing the temp buff, or marking used/free.

}

void sendTelemetry(telemetryPacket_t * packet){

			csp_conn_t * conn;
			csp_packet_t * outPacket;
			conn = csp_connect(2,0,4,1000,0);	//Create a connection. This tells CSP where to send the data (address and destination port).
			outPacket = csp_buffer_get(TELEM_HEADER_SIZE+packet->length);

			memcpy(&outPacket->data[0],&packet->timestamp,sizeof(Calendar_t));
			memcpy(&outPacket->data[sizeof(Calendar_t)],&packet->telem_id,1);
			memcpy(&outPacket->data[sizeof(Calendar_t)+1],&packet->length,1);

			//Only do this if there is data.
			if(packet->length){
				memcpy(&outPacket->data[sizeof(Calendar_t)+2],packet->data,packet->length);
			}


			int good = csp_send(conn,outPacket,0);
			csp_close(conn);

			if(!good){

				csp_buffer_free(outPacket);
			}
}
