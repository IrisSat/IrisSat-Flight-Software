#ifndef INCLUDE_WATCHDOG_H_
#define INCLUDE_WATCHDOG_H_
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// License:
//  Available under MIT license.
//
// Repository:
//  Github: https://github.com/UMSATS/cdh-tsat5
//
// File Description:
//  Functions for manipulating and configuring the watchdog.
//
// History
// 2019-04-16 by Tamkin Rahman
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "drivers/mss_watchdog/mss_watchdog.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

// The MSS Watchdog can be configured (in Libero) by specifying the:
// - Reload value      (i.e. 0x1800000)
// - Counter Threshold (i.e. 0xFFFFFFFF)
//
// If the reload value is greater than the counter threshold, then the watchdog cannot be
// reset here.
//
// The reload value corresponds to 64 ticks of the RC Oscillator (50 MHz). Hence, the
// watchdog period can be calculated like so:
//
// <Reload Value> * 64 / (50*10^6) = Period (in seconds)
//
// The following Watchdog period assumes a reload value of 0x1800000 (i.e. the minimum possible).
#define WD_PERIOD_s           32

#define WD_TASK_PERIOD_ms     WD_PERIOD_s * (1000 / 2)

// Call this to initialize the watchdog.
#define init_WD()             MSS_WD_init()

// Call this to service the watchdog. This function is not atomic. Assume that the counter threshold
// is larger than the reload value (this guarantees that the watchdog can be reloaded any time).
#define service_WD()          MSS_WD_reload()

// Call this to check whether this device reset due to a watchdog timeout.
#define timeout_occured_WD()  MSS_WD_timeout_occured()

// Call this to clear a timeout event.
#define clear_timeout_WD()    MSS_WD_clear_timeout_event()

#endif // INCLUDE_WATCHDOG_H
