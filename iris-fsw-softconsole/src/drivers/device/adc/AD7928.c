//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  Driver for communicating with the AD7928 ADC.
//
// History
// 2021-03-24 by Joseph Howarth
// - Created.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "drivers/device/adc/AD7928.h"
#include "drivers/protocol/spi.h"
#include "board_definitions.h"
#include <FreeRTOS-Kernel/include/FreeRTOS.h>
#include <FreeRTOS-Kernel/include/task.h>

void readADC(AD7928_Measurement_t* measurement){

    //Write to cmd reg, normal range (0 to Vref), binary coding, channel 0.
    uint16_t fullCmd = AD7928_WRITE_BIT + AD7928_RANGE + AD7928_CODING;

    uint8_t cmd[2];
    cmd[0] = fullCmd >>8;
    cmd[1] = fullCmd &(0xFF);

    spi_transaction_block_write_without_toggle(ADC_SPI_CORE, ADC_SLAVE_CORE, &cmd, 2, NULL, 0);

    //Wait at least 50 ns (tQuiet), here wait 1 ms
    if(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING){
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    uint8_t result[2] = {0};
    //Get the value.
    spi_transaction_block_read_without_toggle(ADC_SPI_CORE, ADC_SLAVE_CORE, NULL, 0, result, 2);

    measurement->channel =result[0]>>(AD7928_ADD0>>8);
    measurement->value = (*((uint16_t*)result)) & (0x0FFF);

}

