//-------------------------------------------------------------------------------------------------
// File Description:
//  This file contains tests related to the ad.
//
// History
// 2021-03-24 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------

#include "tests.h"
#include "drivers/device/adc/adc_common.h"
#include <FreeRTOS-Kernel/include/FreeRTOS.h>
#include <FreeRTOS-Kernel/include/task.h>

void vTestADC(void * pvParams){

    double temp =0;

    while(1){

        //Get the board temp.Manually compare to external thermometer....
        temp = getBoardTemp();

        vTaskDelay(pdMS_TO_TICKS(500));

    }
}
