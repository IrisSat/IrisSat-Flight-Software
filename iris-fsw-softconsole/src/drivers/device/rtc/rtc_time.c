//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  User-facing RTC module for reading, writing, and validating the internal and external RTC.
//
// History
// 2019-04-18 by Tamkin Rahman
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "rtc_time.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Number of times to retry when resyncing.
#define RETRY_COUNT      3

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef UNIT_TESTING
void init_rtc()
{
	// Initialize the external RTC and the internal RTC, and copy the external RTC date into the internal RTC.
	ds1393_init();
	MSS_RTC_init(MSS_RTC_CALENDAR_MODE, TICKS_TO_SECONDS);
	MSS_RTC_start();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
ErrCodesRTC_t resync_rtc()
{
	ErrCodesRTC_t rc = TIME_UNKNOWN_ERROR;
	Calendar_t time;
	time.week = 1; // Must be at least 1.

	for (int ix = 0; ((ix < RETRY_COUNT) && (rc != TIME_SUCCESS)); ix++)
	{
		ds1393_read_time(&time);
		rc = time_valid(&time);
	}
	if (TIME_SUCCESS == rc)
	{
		MSS_RTC_set_calendar_count(&time);
	}
    else
    {
        rc = TIME_UNKNOWN_ERROR;
    }

	return rc;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void set_rtc(Calendar_t * time)
{
	ds1393_write_time(time);
	resync_rtc();
}
#endif

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
ErrCodesRTC_t time_valid(Calendar_t * time)
{
    ErrCodesRTC_t rc = TIME_UNKNOWN_ERROR;

    if (time->second > MAX_SECONDS)
    {
        rc = TIME_SECONDS_INVALID;
    }
    else if (time->minute > MAX_MINUTES)
    {
        rc = TIME_MINUTES_INVALID;
    }
    else if (time->hour > MAX_HOURS)
    {
        rc = TIME_HOURS_INVALID;
    }
	else if ((time->day < MIN_DAYS) || (time->day > MAX_DAYS))
    {
        rc = TIME_DAYS_INVALID;
    }
    else if ((time->month < MIN_MONTHS) || (time->month > MAX_MONTHS))
    {
        rc = TIME_MONTHS_INVALID;
    }
    else if (time->year > MAX_YEARS)
    {
        rc = TIME_YEARS_INVALID;
    }
    else
    {
        rc = TIME_SUCCESS;
    }

    return rc;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long calendar_to_long(Calendar_t * time){
	return CALENDAR_TO_LONG(time);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int compare_time(Calendar_t * time1, Calendar_t * time2)
{
	int result = 0;
	unsigned long time1_long = CALENDAR_TO_LONG(time1);
	unsigned long time2_long = CALENDAR_TO_LONG(time2);

	if (time1_long < time2_long)
	{
		result = -1;
	}
	else if (time1_long > time2_long)
	{
		result = 1;
	}
	// Else, they are equal, and the result is 0.

	return result;
}
