//-------------------------------------------------------------------------------------------------
// File Description:
//  This file contains tests related to SPI communication.
//
// History
// 2020-04-21 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------

#include "tests.h"

#include "FreeRTOS.h"
#include "task.h"
#include "spi.h"

void vTestSPI(void *pvParameters)
{
    uint8_t test_cmd[] = {0x55, 0x56};
    uint8_t test_wr[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    uint8_t test_rd[4];

    const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);

    for (;;)
    {
        vTaskSuspendAll();
        // Write a block every second.
        spi_transaction_block_write_without_toggle(
                    CORE_SPI_0,
                    SPI_SLAVE_0,
					MSS_GPIO_0,
                    test_cmd,
                    sizeof(test_cmd) / sizeof(test_cmd[0]),
                    test_wr,
                    sizeof(test_wr) / sizeof(test_wr[0])
                );
        xTaskResumeAll();

        taskYIELD();
        vTaskSuspendAll();
        spi_transaction_block_read_without_toggle(
                    CORE_SPI_0,
                    SPI_SLAVE_0,
					MSS_GPIO_0,
                    test_cmd,
                    sizeof(test_cmd) / sizeof(test_cmd[0]),
                    test_rd,
                    sizeof(test_rd) / sizeof(test_rd[0])
                );
        xTaskResumeAll();
        vTaskDelay(xDelay1000ms);
    }
}
