#include "can.h"
#include "arch/csp_thread.h"
#include "interfaces/csp_if_can.h"

typedef uint32_t can_id_t;

/** CAN Frame */
typedef struct {
	/** 32 bit CAN identifier */
	can_id_t id;
	/** Data Length Code */
	uint8_t dlc;
	/**< Frame Data - 0 to 8 bytes */
	union __attribute__((aligned(8))) {
		uint8_t data[8];
		uint16_t data16[4];
		uint32_t data32[2];
	};
} can_frame_t;

typedef enum {
	CAN_ERROR = 0,
	CAN_NO_ERROR = 1,
} can_error_t;


int can_send(can_id_t id, uint8_t * data, uint8_t dlc);



int can_init(uint32_t id, uint32_t mask, struct csp_can_config *conf){
	QueueHandle_t *que = get_csp_can_queue();
	init_CAN(CAN_BAUD_RATE_250K,que);

	return 0;

}

int can_send(can_id_t id, uint8_t * data, uint8_t dlc){
	
	CANMessage_t frame;
		
	int i, tries = 0;

	if (dlc > 8)
		return -1;

	#define CAN_EFF_FLAG  1
	/* Copy identifier */
	frame.id = id | CAN_EFF_FLAG; //Use Extended Frame Format flag.


	/* Copy data to frame */
	for (i = 0; i < dlc; i++)
		frame.data[i] = data[i];

	/* Set DLC */
	frame.dlc = dlc;

	/* Send frame */

	uint8_t transmit_complete=0;
	while(!transmit_complete){
		
		if(CAN_TRANSMIT_READY()){
			
		transmit_complete = CAN_transmit_message(&frame);
		
			
		}
		else{
			csp_sleep_ms(10);
		}
	}

	return 0;
}
