//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// License:
// 	Available under the GNU General Public License v3.0 (GPL-3.0-or-later)
//
// Repository:
//  Github: https://github.com/UMSATS/cdh-tsat5
//
// File Description:
//  SPI tasks and functions. Currently contains test code.
//
// History
// 2019-02-08 by Tamkin Rahman
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "cdh_tsat5_system_hw_platform.h" // Contains the address of the CORE_SPI instance for the driver.
#include "drivers/CoreSPI/core_spi.h"	// Contains the interface for the CoreSPI drivers.

SPI_instance_t core_spi_0; // Initialized by CoreSPI initialization function.

void init_spi()
{
	// NOTE: Look at core_spi.h for descriptions for all the functions used.
	uint8_t test_tx = 0x55;
	uint8_t test_rx = 0x99;

	// Initialize the core SPI instance. Note that with PCLK_DIV_256, the clock period is ~2 us (i.e. 256 / 144 MHz).
	// With PCLK_DIV_128, the clock period is ~1 us. And so on. Keep this in mind when using a
	// logic analyzer, as depending on the sample rate, it will not pick up the faster clock rates.
	SPI_init(&core_spi_0, CORESPI_0_0, SPI_MODE_MASTER, SPI_MODE2, PCLK_DIV_256);
	SPI_enable(&core_spi_0);

	// Optionally, you can configure a slave individually.
	//SPI_configure(&core_spi_0, SPI_SLAVE_0, SPI_MODE2, PCLK_DIV_2, SPI_MSB_FIRST);

	// Perform a slave select prior to writing any data.
	SPI_slave_select(&core_spi_0, SPI_SLAVE_0);

	// For some reason, this function doesn't seem to "just work" for writing a 8-bit value to SPI.
	//rc = SPI_write_byte(&core_spi_0, &test_tx);

	// Use this "block_read" function instead to send a command, and then read in the data.
	// SPI_block_read(&core_spi_0, &test_tx, 1, &test_rx, 1);

	// Use this "block_write" function instead to send a command, and then send in the data.
	SPI_block_write(&core_spi_0, &test_tx, 1, &test_rx, 1);

	SPI_disable(&core_spi_0);
}
