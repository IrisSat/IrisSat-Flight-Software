//-------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//	Github: https://github.com/joehowarth17/IrisSat-Flight-Software
//
// File Description:
//  This file contains tests related to CAN bus communication.
//
// History
// 2020-04-21 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------

#include "tests.h"

#include "FreeRTOS.h"
#include "task.h"
#include "can.h"


void vTestCANTx(void *pvParameters)
{
    const TickType_t delay = pdMS_TO_TICKS(100);
    CANMessage_t msg = {
                        0x321,
                        1,
                        8,
                        {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}
                     };
    for (;;)
    {
        if (CAN_TRANSMIT_READY())
        {
            CAN_transmit_message(&msg);
        }
        vTaskDelay(delay);
    }
}


void vTestCANRx(void *pvParameters)
{
    int messages_processed = 0;
    CANMessage_t rx_msg;
    for (;;)
    {
        if (xQueueReceive(can_rx_queue, &rx_msg, portMAX_DELAY) == pdTRUE)
        {
            messages_processed++;
        }
    }
}
