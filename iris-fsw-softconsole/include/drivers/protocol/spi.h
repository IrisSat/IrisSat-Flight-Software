#ifndef INCLUDE_SPI_H_
#define INCLUDE_SPI_H_
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
#include "drivers/CoreSPI/core_spi.h"   // Contains the interface for the CoreSPI drivers.
#include "drivers/mss_gpio/mss_gpio.h"
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
    CORE_SPI_1,
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
//	Note:	The fifo length or each CoreSPI peripheral can only be changed in the
// 			Libero project. The fifo lengths must be updated.
//  	   	in the spi.c file if changed.
//
//	TODO: Check if clock speed can be updated through software. There is no
//        function in the driver but CoreSPI user guide says this is possible.
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
spi_instance_t * get_spi_instance(
    CoreSPIInstance_t core // The SPI core (master) to fetch.
    );

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Configure a slave instance. If a slave is not configured, a default configuration is used.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//void spi_configure_slave(
//    CoreSPIInstance_t core,             // The SPI core (master) to use.
//    spi_slave_t slave,                  // The SPI slave to configure.
//    SPI_protocol_mode_t protocol_mode,  // The SPI protocol mode.
//    SPI_pclk_div_t clk_rate,            // The SPI clock rate.
//    SPI_order_t data_xfer_order         // The SPI data transfer order (MSB or LSB).
//    );

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Configure a GPIO for use as a slave select. This will initialize the pin, and the slave select pin to inactive. This is for use with functions with
//  "_without_toggle" at the end. By default, the CoreSPI driver will toggle the slave select between byte transfers, and so this can be added to register a
//  GPIO pin to use as the slave select instead.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_configure_gpio_ss(mss_gpio_id_t pin);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Perform a slave select, send a command, write data to a slave, and then disable the slave select. The slave
//  select is toggled between each byte transfer.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_transaction_block_write_with_toggle(
	CoreSPIInstance_t core,  // The SPI core used.
	spi_slave_t slave,       // The SPI slave configuration to use.
	uint8_t * cmd_buffer,    // The buffer containing the command.
	size_t cmd_size,         // The size of the command buffer.
	uint8_t * wr_buffer,     // The buffer containing the data to write.
	size_t wr_size           // The size of the write buffer.
    );

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Perform a slave select, send a command, read data from a slave, and then disable the slave select. The slave
//  select is toggled between each byte transfer.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_transaction_block_read_with_toggle(
	CoreSPIInstance_t core,  // The SPI core used.
	spi_slave_t slave,       // The SPI slave configuration to use.
	uint8_t * cmd_buffer,    // The buffer containing the command.
	size_t cmd_size,         // The size of the command buffer.
	uint8_t * rd_buffer,     // The buffer containing the data to write.
	size_t rd_size           // The size of the write buffer.
    );

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Perform a slave select, send a command, write data to a slave, and then disable the slave select. The slave
//  select is held low (i.e. not toggled) between each byte transfer.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_transaction_block_write_without_toggle(
    CoreSPIInstance_t core,  // The SPI core used.
    spi_slave_t slave,       // The SPI slave configuration to use.
	mss_gpio_id_t pin,       // The GPIO pin to use for the slave select.
    uint8_t * cmd_buffer,    // The buffer containing the command.
    uint16_t cmd_size,         // The size of the command buffer.
    uint8_t * wr_buffer,     // The buffer containing the data to write.
	uint16_t wr_size           // The size of the write buffer.
    );

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Perform a slave select, send a command, read data from a slave, and then disable the slave select. The slave
//  select is held low (i.e. not toggled) between each byte transfer.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void spi_transaction_block_read_without_toggle(
    CoreSPIInstance_t core,  // The SPI core used.
    spi_slave_t slave,       // The SPI slave configuration to use.
	mss_gpio_id_t pin,       // The GPIO pin to use for the slave select.
    uint8_t * cmd_buffer,    // The buffer containing the command.
    uint16_t cmd_size,         // The size of the command buffer.
    uint8_t * rd_buffer,     // The buffer containing the data to write.
	uint16_t rd_size           // The size of the write buffer.
    );

#endif /* INCLUDE_SPI_H_ */
