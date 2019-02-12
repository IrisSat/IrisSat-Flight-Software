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
//  SPI tasks and functions for SPI masters. Functions with "rtos" in their name must be called from a FreeRTOS thread, as they use mutex
//  objects to manage use of the core.
//
// History
// 2019-02-08 by Tamkin Rahman
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "spi.h"

#include "cdh_tsat5_system_hw_platform.h" // Contains the address of the CORE_SPI instance for the driver.
#include "FreeRTOS.h"
#include "semphr.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// GLOBALS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
SPI_instance_t core_spi[NUM_SPI_INSTANCES]; // Initialized by CoreSPI initialization function.
SemaphoreHandle_t core_lock[NUM_SPI_INSTANCES]; // Semaphores for the mutex locks. Seems to be that for short operations (e.g. even 80 ms), a mutex is good: http://www.openrtos.net/FreeRTOS_Support_Forum_Archive/December_2014/freertos_FreeRTOS_FatFs_Works_only_with_taskENTER_CRITICAL_5dc853ffj.html

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int init_spi()
{
    int rc = 1;

    for (int ix = 0; ix < NUM_SPI_INSTANCES; ix++)
    {
        core_lock[ix] = xSemaphoreCreateMutex();
        if (core_lock[ix] == NULL)
        {
            rc = 0;
            break; // Break out of this for loop.
        }
    }

    if (rc)
    {
      // Initialize the core SPI instance. Note that with PCLK_DIV_256, the clock period is ~2 us (i.e. 256 / 144 MHz).
      // With PCLK_DIV_128, the clock period is ~1 us. And so on. Keep this in mind when using a
      // logic analyzer, as depending on the sample rate, it will not pick up the faster clock rates.
      SPI_init(&core_spi[CORE_SPI_0], CORESPI_0_0, SPI_MODE_MASTER, SPI_MODE0, PCLK_DIV_256);
    }

    return rc;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
SPI_instance_t * get_spi_instance(CoreSPIInstance_t core)
{
    return &core_spi[core];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_configure_slave(CoreSPIInstance_t core, SPI_slave_t slave, SPI_protocol_mode_t protocol_mode, SPI_pclk_div_t clk_rate, SPI_order_t data_xfer_order)
{
    SPI_configure(&core_spi[core], slave, protocol_mode, clk_rate, data_xfer_order);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int spi_rtos_block_write(CoreSPIInstance_t core, SPI_slave_t slave, uint8_t * cmd_buffer, size_t cmd_size, uint8_t * wr_buffer, int wr_size)
{
    int rc = 1;
    if( xSemaphoreTake(core_lock[core], portMAX_DELAY) == pdTRUE )
    {
        SPI_enable(&core_spi[core]);
        SPI_slave_select(&core_spi[core], slave);
        SPI_block_write(&core_spi[core], cmd_buffer, cmd_size, wr_buffer, wr_size);
        SPI_disable(&core_spi[core]);

        xSemaphoreGive(core_lock[core]);
    }
    else
    {
        rc = 0;
    }

  return rc;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int spi_rtos_block_read(CoreSPIInstance_t core, SPI_slave_t slave, uint8_t * cmd_buffer, size_t cmd_size, uint8_t * rd_buffer, int rd_size)
{
    int rc = 1;
    if( xSemaphoreTake(core_lock[core], portMAX_DELAY) == pdTRUE )
    {
        SPI_enable(&core_spi[core]);
        SPI_slave_select(&core_spi[core], slave);
        SPI_block_read(&core_spi[core], cmd_buffer, cmd_size, rd_buffer, rd_size);
        SPI_disable(&core_spi[core]);

        xSemaphoreGive(core_lock[core]);
    }
    else
    {
        rc = 0;
    }

    return rc;
}
