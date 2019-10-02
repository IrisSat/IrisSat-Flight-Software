//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// Repository:
//  UMSATS GitHub cdh-tsat5: Command and Data Handling (CDH) for TSAT5
//
// File Description:
//  Custom task scheduler. Uses a queue of time-tagged tasks to be executed at a given future time.
//
// History
// 2019-09-08 by Eric Kapilik
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RTC Libraries
#include <rtc_common.h>
#include "drivers/mss_rtc/mss_rtc.h"

// FreeRTOS Libraries
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// User Libraries
#include "scheduler.h"
#include <rtc_time.h>
#include <request_code.h>



//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define MAX_QUEUE_LENGTH					(10)	// The maximum number of items that the queue can hold at any one time.
#define SCHEDULER_TASK_DELAY_MS				(2000)	// The delay time of each task cycle in ms.
#define DEQUEUE_MS_TO_WAIT					(100)	// The maximum amount of time (in ms) the task should remain in the Blocked state to wait to dequeue data.
#define ENQUEUE_MS_TO_WAIT					(100)	// The maximum amount of time (in ms) the task should remain in the Blocked state to wait to enqueue data.

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ENUMS AND ENUM TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTS AND STRUCT TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description: Holds a desired execution time along with a request code.
//
//	time_tag: the desired future execution time of the request
//  request_code: the code of the predefined task to execute
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	mss_rtc_calendar_t time_tag;
	request_code_t request_code;
} time_tagged_task_t;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static QueueHandle_t task_queue_handler;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Initializes the queue for holding tasks.
//
// Returns:
//  On success returns handler to Queue (QueueHandle_t), on failure returns NULL.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static QueueHandle_t init_queue();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Kills process and cleans up resources.
//
// Returns:
//  On success returns 0, on failure returns -1.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static int clean_up_resources();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static QueueHandle_t init_queue(){
	return xQueueCreate(MAX_QUEUE_LENGTH, sizeof(time_tagged_task_t) );
}

static int clean_up_resources(){
	if(task_queue_handler != NULL){
		vQueueDelete(task_queue_handler);
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void vTaskScheduler(void *pvParameters){
	task_queue_handler = init_queue(); // Initialize the queue for holding the time tagged tasks
	const TickType_t queue_timeout_ms = pdMS_TO_TICKS(DEQUEUE_MS_TO_WAIT);
	static time_tagged_task_t front_task; // Static buffer for holding the front task read from queue.
	static BaseType_t rslt; // Variable to hold result of various functions

	// Get Test data for calendar
	static mss_rtc_calendar_t *p_rtc_calendar;
	p_rtc_calendar = malloc(sizeof(mss_rtc_calendar_t));
	MSS_RTC_get_calendar_count(p_rtc_calendar);
	schedule_task(test_code_0, *p_rtc_calendar);
	free(p_rtc_calendar);

	//TODO: Ensure Internal RTC is synchronized with External RTC.

	for( ;; ) {
		//TODO: Check priority queue for task scheduled for current_time

		rslt = xQueuePeek(task_queue_handler, &front_task, queue_timeout_ms); // Peek at front task in queue.

		if(rslt == errQUEUE_EMPTY){// Queue is empty.
			continue;  // Go back to beginning of loop.
		}
		else if(rslt == pdPASS){ // Data successfully read from the queue.
			continue; // Go back to beginning of loop.
			// Check if time is current time.
		}
		vTaskDelay(pdMS_TO_TICKS(SCHEDULER_TASK_DELAY_MS));
	}

	clean_up_resources(); // Clean up resources before exiting task.
}

int schedule_task(request_code_t req, mss_rtc_calendar_t time){
	//TODO: schedule into priority queue, use rtc_time.h>calendar_to_long for priority
	//if(task_queue_handler == NULL) { return -1; } // ERROR: queue not yet initialized
	//TODO: check if full


	//static time_tagged_task_t pvTask; // private task to be initialized with parameters and copied into Queue.

	//pvTask.request_code = req;
	//pvTask.time_tag = time;

	//xQueueSendToBack(task_queue_handler, &pvTask, queue_timeout_ms);
	return 0;
}
