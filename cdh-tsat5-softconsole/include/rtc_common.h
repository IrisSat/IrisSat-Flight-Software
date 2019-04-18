#ifndef RTC_COMMON_H_
#define RTC_COMMON_H_
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// License:
//  Available under the GNU General Public License v3.0 (GPL-3.0-or-later)
//
// Repository:
//  Github: https://github.com/UMSATS/cdh-tsat5
//
// File Description:
//  Common definitions and macros for all RTC types.
//
// History
// 2019-04-17 by Tamkin Rahman
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "cpu_types.h"
#include "drivers/mss_rtc/mss_rtc.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define MIN_SECONDS 0u
#define MAX_SECONDS 59u

#define MIN_MINUTES 0u
#define MAX_MINUTES 59u

#define MIN_HOURS 0u
#define MAX_HOURS 23u

#define MIN_DAYS 1u
#define MAX_DAYS 31u

#define MIN_MONTHS 1u
#define MAX_MONTHS 12u

#define MIN_YEARS 70u
#define YEAR_OFFSET 1970u


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTURES AND STRUCTURE TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *
 * The calendar type will have the following restrictions:
	typedef struct
	{
		uint8_t second;  // The current seconds (0-59).
		uint8_t minute;  // The current minutes (0-59).
		uint8_t hour;    // The current hour (0-23).
		uint8_t day;     // The current day (1-31).
		uint8_t month;   // The current month (1-12).
		uint8_t year;    // The current year (70 or greater, with 70 being 1970).
		uint8_t weekday; // The current weekday (1-7, with 1 being Sunday).
		uint8_t week;    // Not used. Kept for backward compatibility with MSS_RTC. MUST BE 1 or greater.
	} Calendar_t;
*/

typedef mss_rtc_calendar_t Calendar_t;



#endif /* RTC_COMMON_H_ */
