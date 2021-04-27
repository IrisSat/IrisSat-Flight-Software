/*
 * telemetry.h
 *	Note telemetry and command is used interchangably here.
 *  Created on: Mar. 17, 2021
 *      Author: Joseph Howarth
 */

#ifndef INC_TELEMETRY_H_
#define INC_TELEMETRY_H_

#include <stdint.h>
#include "drivers/device/rtc/rtc_common.h"
#include <csp/csp.h>

//Define the csp address of all devices in the network.
#define POWER_CSP_ADDRESS	2
#define COMMS_CSP_ADDRESS	3
#define CDH_CSP_ADDRESS		4
#define PAYLOAD_CSP_ADDRESS	5
#define GROUND_CSP_ADDRESS	9


//Define the ports we're using
#define CSP_CMD_PORT	7
#define CSP_TELEM_PORT	8
#define CSP_UPDATE_PORT	9

/***********************************************************/
//Put the commands/telemtry here.

//Payload telemetry.
typedef enum {
PAYLOAD_POWER_GOOD_ID = 0,
PAYLOAD_BOARD_TEMP_ID,
PAYLOAD_SAMPLE_TEMP_ID,
PAYLOAD_FULL_IMAGE_ID,
PAYLOAD_R_REFLECTANCE_ID,
PAYLOAD_G_REFLECTANCE_ID,
PAYLOAD_B_REFLECTANCE_ID,
PAYLOAD_SAMPLE_LOC_ID,
PAYLOAD_CAMERA_TIME_ID,
PAYLOAD_ERROR_ID,
NUM_PAYLOAD_TELEMETRY
} payloadTelemetry_t;

typedef enum {
PAYLOAD_POWER_GOOD_CMD = 0,
PAYLOAD_BOARD_TEMP_CMD,
PAYLOAD_SAMPLE_TEMP_CMD,
PAYLOAD_FULL_IMAGE_CMD,
PAYLOAD_R_REFLECTANCE_CMD,
PAYLOAD_G_REFLECTANCE_CMD,
PAYLOAD_B_REFLECTANCE_CMD,
PAYLOAD_SAMPLE_LOC_CMD,
PAYLOAD_CAMERA_TIME_CMD,
PAYLOAD_ERROR_CMD,
NUM_PAYLOAD_COMMANDS
} payloadCommands_t;


typedef enum {
CDH_SCHEDULE_TTT_CMD =0,
CDH_DOWNLOAD_IMAGE_CMD,
NUM_CDH_COMMANDS
} cdhCommands_t;

typedef enum {
TASK_TAKE_IMAGE =0,
NUM_CDH_TASK
} cdhTask_t;

/**********************************************************/

//typedef struct{
//	uint8_t second;
//	uint8_t minute;
//	uint8_t hour;
//	uint8_t day;
//	uint8_t month;
//	uint8_t year;
//	uint8_t weekday;
//	uint8_t week;
//
//}Calendar_t;


typedef struct{

	Calendar_t timestamp;
	uint8_t telem_id;		//Make sure there is less than 255 commands/telemetry ids for any subsystem. Or change to uint16_t.
	uint8_t length;
	uint8_t* data;

} telemetryPacket_t;


/**********************************************************/
void unpackTelemetry(uint8_t * data, telemetryPacket_t* output);//Unpacks the telemetry into the telemetry packet struct.
void sendTelemetry(telemetryPacket_t * packet);//Sends telemetry to CDH.
void sendTelemetry_direct(telemetryPacket_t * packet,csp_conn_t * conn); //For directly responding to a message.
void sendCommand(telemetryPacket_t * packet,uint8_t addr);//Sends a cmd packet to the cmd port of the subsytem at address addr.
void sendTelemetryAddr(telemetryPacket_t * packet,uint8_t addr); //Sends telemetry directly to a subsystem.

/**********************************************************/

#endif /* INC_TELEMETRY_H_ */
