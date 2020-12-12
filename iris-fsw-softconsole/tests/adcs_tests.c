//-------------------------------------------------------------------------------------------------
// File Description:
//  This file contains tests related to the adcs system.
//
// History
// 2020-04-21 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------

#include <FreeRTOS/include/FreeRTOS.h>
#include <FreeRTOS/include/task.h>
#include "tests.h"

#include "drivers/device/adcs_driver.h"

void vTestAdcsDriver(void * pvParameters){


    uint8_t telemetryData [ADCS_TELEMETRY_TOTAL_SIZE] = {0xFF};
    uint8_t telemetryData2 [ADCS_MAGNETORQUER_DATA_SIZE] = {0xFF};
    while(1){

        AdcsDriverError_t result = adcs_power_on();
        if(!result){
            while(1);
        }

        result = adcs_reset();
        if(!result){
            while(1);
        }

        result = adcs_initiate_telemetry();
        if(!result){
            while(1);
        }


        result = adcs_read_telemetry(telemetryData);
        if(!result){
            while(1);
        }
        //Verify the telemetry data here.
        uint8_t pwm_cycle = 128; // This gives a 50% duty cycle.
        result = adcs_turn_on_magnetorquer(MAGNETORQUER_X, pwm_cycle);
        if(!result){
            while(1);
        }
       result = adcs_turn_on_magnetorquer(MAGNETORQUER_Y,pwm_cycle);
        if(!result){
            while(1);
        }
        result = adcs_turn_on_magnetorquer(MAGNETORQUER_Z,pwm_cycle);
        if(!result){
            while(1);
        }

        result = adcs_turn_off_magnetorquer(MAGNETORQUER_X);
        if(!result){
            while(1);
        }
        result = adcs_turn_off_magnetorquer(MAGNETORQUER_Y);
        if(!result){
            while(1);
        }
        result = adcs_turn_off_magnetorquer(MAGNETORQUER_Z);
        if(!result){
            while(1);
        }


        result = adcs_read_magnetorquer_data(telemetryData2);
        if(!result){
            while(1);
        }
        //Verify the telemetry data here.

        vTaskDelay(pdMS_TO_TICKS(2500)); // Repeat the test every 2.5 seconds.
    }

}
