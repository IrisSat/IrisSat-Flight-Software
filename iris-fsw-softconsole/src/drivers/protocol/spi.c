//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  SPI tasks and functions for SPI masters.
//
// History
// 2019-02-08 by Tamkin Rahman
// - Created.
// 2019-02-24 by Tamkin Rahman
// - Remove the use of mutex within spi.c functions. Instead, the user will have access to the mutexes via the header file.
// 2019-03-28 by Tamkin Rahman
// - Correct file description.
// 2019-04-17 by Tamkin Rahman
// - Allow the user to register a GPIO to use as the slave select to avoid toggling the slave select between byte transfers. Also,
//   add new functions to allow the user to use a GPIO for the slave select.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "drivers/protocol/spi.h"

#include <string.h>	//For memcpy.

#include <firmware/MSS_C0_hw_platform.h> // Contains the address of the CORE_SPI instance for the driver.

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define SS_DISABLE_GPIO_STATE 1
#define SS_ENABLE_GPIO_STATE  0

#define SPI_GPIO_SS_ENABLE(pin)   MSS_GPIO_set_output((pin), SS_ENABLE_GPIO_STATE)
#define SPI_GPIO_SS_DISABLE(pin)  MSS_GPIO_set_output((pin), SS_DISABLE_GPIO_STATE)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// GLOBALS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
spi_instance_t core_spi[NUM_SPI_INSTANCES]; // Initialized by CoreSPI initialization function.
SemaphoreHandle_t core_lock[NUM_SPI_INSTANCES]; // Semaphores for the mutex locks. Seems to be that for short operations (e.g. even 80 ms), a mutex is good: http://www.openrtos.net/FreeRTOS_Support_Forum_Archive/December_2014/freertos_FreeRTOS_FatFs_Works_only_with_taskENTER_CRITICAL_5dc853ffj.html

//The base address for each CoreSPI peripheral.
addr_t core_base_addr[NUM_SPI_INSTANCES] = {	CORESPI_C0_0,
                                                CORESPI_C1_0 };
//The length of each CoreSPI fifo.
uint16_t core_fifo_len[NUM_SPI_INSTANCES] = {	8,
												8};
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
    	for(int ix = 0; ix < NUM_SPI_INSTANCES; ix++){
		  // Initialize the core SPI instance. Make sure the fifo depth matches
		  // the value set in the Libero project
		  SPI_init(&core_spi[ix], core_base_addr[ix], core_fifo_len[ix]);

		  SPI_configure_master_mode(&core_spi[ix]);

    	}
    }

    return rc;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
spi_instance_t * get_spi_instance(CoreSPIInstance_t core)
{
    return &core_spi[core];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//void spi_configure_slave(CoreSPIInstance_t core, spi_slave_t slave, SPI_protocol_mode_t protocol_mode, SPI_pclk_div_t clk_rate, SPI_order_t data_xfer_order)
//{
//    SPI_configure(&core_spi[core], slave, protocol_mode, clk_rate, data_xfer_order);
//}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_configure_gpio_ss(mss_gpio_id_t pin)
{
    MSS_GPIO_config( pin, MSS_GPIO_OUTPUT_MODE );
    MSS_GPIO_set_output( pin, SS_DISABLE_GPIO_STATE );
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_transaction_block_write_with_toggle(CoreSPIInstance_t core, spi_slave_t slave, uint8_t * cmd_buffer, size_t cmd_size, uint8_t * wr_buffer, size_t wr_size)
{
//    SPI_enable(&core_spi[core]);
//    SPI_slave_select(&core_spi[core], slave);
//    SPI_block_write(&core_spi[core], cmd_buffer, cmd_size, wr_buffer, wr_size);
//    SPI_disable(&core_spi[core]);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_transaction_block_read_with_toggle(CoreSPIInstance_t core, spi_slave_t slave, uint8_t * cmd_buffer, size_t cmd_size, uint8_t * rd_buffer, size_t rd_size)
{
//    SPI_enable(&core_spi[core]);
//    SPI_slave_select(&core_spi[core], slave);
//    SPI_block_read(&core_spi[core], cmd_buffer, cmd_size, rd_buffer, rd_size);
//    SPI_disable(&core_spi[core]);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_transaction_block_write_without_toggle(CoreSPIInstance_t core, spi_slave_t slave, mss_gpio_id_t pin, uint8_t * cmd_buffer, uint16_t cmd_size, uint8_t * wr_buffer, uint16_t wr_size)
{
	//TODO: Should we use a static buffer instead of malloc? If not we need to handle if malloc fails.

	//Put the command and data into one buffer.
	uint32_t total_count = cmd_size + wr_size;
	uint8_t * buffer = pvPortMalloc(total_count);

	memcpy(buffer,cmd_buffer,cmd_size);
	memcpy(&buffer[cmd_size],wr_buffer,wr_size);

	//Select the slave and then perform SPI transfer.
    SPI_set_slave_select(&core_spi[core], slave);
    SPI_transfer_block(&core_spi[core],buffer, total_count, 0, 0);
    SPI_clear_slave_select(&core_spi[core],slave);

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_transaction_block_read_without_toggle(CoreSPIInstance_t core, spi_slave_t slave, mss_gpio_id_t pin, uint8_t * cmd_buffer, uint16_t cmd_size, uint8_t * rd_buffer, uint16_t rd_size)
{
	//TODO: Should we use a static buffer instead of malloc? If not we need to handle if malloc fails.

    SPI_set_slave_select(&core_spi[core], slave);
    SPI_transfer_block(&core_spi[core], cmd_buffer, cmd_size, rd_buffer, rd_size);
    SPI_clear_slave_select(&core_spi[core],slave);

}
