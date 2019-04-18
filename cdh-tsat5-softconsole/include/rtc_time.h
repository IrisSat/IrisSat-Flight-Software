#ifndef RTC_TIME_H_
#define RTC_TIME_H_
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
//  User-facing RTC module for reading, writing, and validating the internal and external RTC.
//
// History
// 2019-04-18 by Tamkin Rahman
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "rtc_common.h"
#include "rtc_ds1393.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// These should be used to acquire the lock for the RTC SPI core for the "set_rtc" and "resync_rtc" operations
// in FreeRTOS threads.
#define WAIT_FOR_RTC_CORE(delay)      WAIT_FOR_CORE(RTC_SPI_CORE, (delay))
#define WAIT_FOR_RTC_CORE_MAX_DELAY() WAIT_FOR_CORE_MAX_DELAY(RTC_SPI_CORE)
#define RELEASE_RTC_CORE()            RELEASE_CORE(RTC_SPI_CORE)

// Use to read from the RTC.
#define read_rtc(buffer) MSS_RTC_get_calendar_count(buffer)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Initialize the internal and external RTC (without resync). It should only be initialized once the SPI driver has been initialized.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void init_rtc();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Write the date from the external RTC to the internal RTC.
//
// Returns:
//   1, on success,
//   0, on failure (to obtain a valid calendar time)
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int resync_rtc();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Write the given date to the external RTC, and then resync.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void set_rtc(
		Calendar_t * time // Object containing the calendar time to write.
		);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Indicate whether the given calendar time is a valid time.
//
// Returns:
//  1 if the time is valid, 0 otherwise.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int time_valid(
		Calendar_t * time // Object containing the calendar time to check.
		);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Compare two calendar times, and check which is later than the other.
//
// Returns:
//  -1, if time1 is earlier than time2
//  0, if time1 is equal to time2
//  1, if time1 is later than time2
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int compare_time(
		Calendar_t * time1, // The first calendar time to compare.
		Calendar_t * time2  // The second calendar time to compare.
		);

#endif /* RTC_TIME_H_ */
