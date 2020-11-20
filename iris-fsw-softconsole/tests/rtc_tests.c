//-------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//	Github: https://github.com/joehowarth17/IrisSat-Flight-Software
//
// File Description:
//  This file contains tests related to the real time clock.
//
// History
// 2020-04-21 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------

#include "tests.h"

#include "FreeRTOS.h"
#include "task.h"

#include "rtc_time.h"


void vTestRTC(void *pvParameters)
{
    // Test code
    static volatile int error_occurred = 0;

    static Calendar_t buffer = {
            59u, // seconds
            59u, // minutes
            23u, // hours
            28u, // day
            2u, // February
            20u, // year (2020)
            1u, // weekday
            1u, // week (not used), HOWEVER it must be 1 or greater.
    };

    static Calendar_t buffer2;

    vTaskSuspendAll();
    ds1393_write_time(&buffer);
    if (TIME_SUCCESS != resync_rtc())
    {
        error_occurred = 1;
    }
    xTaskResumeAll();

    for (;;)
    {
        vTaskSuspendAll();
        ds1393_read_time(&buffer);
        read_rtc(&buffer2);
        xTaskResumeAll();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
