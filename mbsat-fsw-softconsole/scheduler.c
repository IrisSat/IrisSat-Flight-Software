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

// User Libraries
#include "scheduler.h"
#include "priority_queue.h"
#include <rtc_time.h>
#include <request_code.h>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define SCHEDULER_TASK_DELAY_MS				(2000)	// The delay time of each task cycle in ms.

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ENUMS AND ENUM TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTS AND STRUCT TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static Node* priority_queue_handler;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void init_TaskScheduler(void){
	//TODO: Ensure Internal RTC is synchronized with External RTC.
	//set up static variables
	priority_queue_handler = NULL;
}

time_tagged_task_t* check_queue(mss_rtc_calendar_t time_now){
	// is empty?
	// temp = peek()
	// if temp->time is now
	//  pop()
	// 	return temp
	// else
	//	return INVALID_REQUEST_CODE
	return NULL;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void vTestTaskScheduler(void *pvParameters){
	init_TaskScheduler();

	static BaseType_t rslt; // Variable to hold result of various functions

	// Buffer variable to hold a task
	static time_tagged_task_t task_buf;

	// Get Test data for calendar
	static mss_rtc_calendar_t *p_rtc_calendar;
	p_rtc_calendar = malloc(sizeof(mss_rtc_calendar_t));

	MSS_RTC_get_calendar_count(p_rtc_calendar); // get current time

	// add 60s to current time
	schedule_task(TEST_CODE_1, *p_rtc_calendar); // create task to be executed in 60s
	// add 90s to current time
	schedule_task(TEST_CODE_2, *p_rtc_calendar); // create task to be executed in 90s
	// add 30s to current time
	schedule_task(TEST_CODE_0, *p_rtc_calendar); // create task to be executed in 30s


	for( ;; ) {
		//request = check_queue(mss_rtc_calendar_t time_now)
		//if(request != invalid request_code)
		//execute(request);
		vTaskDelay(pdMS_TO_TICKS(SCHEDULER_TASK_DELAY_MS));
	}

	free(p_rtc_calendar);
}

int schedule_task(request_code_t req, mss_rtc_calendar_t time){
	// construct time_tagged_task_t w/ given values
	//static time_tagged_task_t pvTask; // private task to be initialized with parameters and copied into Queue.
	//pvTask.request_code = req;
	//pvTask.time_tag = time;


	// Check if pq is empty
	//		set pq = new Node(data)
	// else push(data, priority) ***use rtc_time.c>CALENDAR_TO_LONG(time) for priority
	return 0; // sucess, add error codes for failuers
}
