#ifndef INCLUDE_SPI_H_
#define INCLUDE_SPI_H_
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
// 2019-02-24 by Tamkin Rahman
// - Remove the use of mutex within spi.c functions. Instead, the user will have access to the mutexes via the header file.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "drivers/CoreSPI/core_spi.h"   // Contains the interface for the CoreSPI drivers.
#include "FreeRTOS.h"
#include "semphr.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// NOTE: These macros should only be used in FreeRTOS threads.
#define WAIT_FOR_CORE(core, delay) 		( xSemaphoreTake(core_lock[(core)], (delay)) == pdTRUE ) // Macro for acquiring a FreeRTOS mutex for an SPI core.
#define WAIT_FOR_CORE_MAX_DELAY(core) 	WAIT_FOR_CORE(core, portMAX_DELAY)                       // Macro for acquiring a FreeRTOS mutex for an SPI core, with a timeout of portMAX_DELAY.
#define RELEASE_CORE(core) 				xSemaphoreGive(core_lock[(core)])                        // Macro for releasing a FreeRTOS mutex for an SPI core.

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ENUMS AND ENUM TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef enum
{
    CORE_SPI_0,
    NUM_SPI_INSTANCES,
} CoreSPIInstance_t;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// EXTERNS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
extern SemaphoreHandle_t core_lock[NUM_SPI_INSTANCES]; // Semaphores for the mutex locks. Should only be used in FreeRTOS threads.

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Initialize the SPI cores.
//
// Returns:
//  1 on success, 0 on failure.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int init_spi();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Return the object for the SPI instance. An SPI_instance_t object is necessary for using core_spi.h functions.
//
// Returns:
//  The object for the given CoreSPI instance.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
SPI_instance_t * get_spi_instance(
    CoreSPIInstance_t core // The SPI core (master) to fetch.
    );

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Configure a slave instance.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_configure_slave(
    CoreSPIInstance_t core,             // The SPI core (master) to use.
    SPI_slave_t slave,                  // The SPI slave to configure.
    SPI_protocol_mode_t protocol_mode,  // The SPI protocol mode.
    SPI_pclk_div_t clk_rate,            // The SPI clock rate.
    SPI_order_t data_xfer_order         // The SPI data transfer order (MSB or LSB).
    );

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Perform a slave select, send a command, write data to a slave, and then disable the slave select. Should only be used within a FreeRTOS thread.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_transaction_block_write(
    CoreSPIInstance_t core,
    SPI_slave_t slave,
    uint8_t * cmd_buffer,
    size_t cmd_size,
    uint8_t * wr_buffer,
    int wr_size
    );

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Perform a slave select, send a command, read data from a slave, and then disable the slave select. Should only be used within a FreeRTOS thread.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_transaction_block_read(
    CoreSPIInstance_t core,
    SPI_slave_t slave,
    uint8_t * cmd_buffer,
    size_t cmd_size,
    uint8_t * rd_buffer,
    int rd_size
    );

#endif /* INCLUDE_SPI_H_ */
