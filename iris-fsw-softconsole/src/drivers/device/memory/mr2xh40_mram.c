//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  Driver for the MR2xH40 MRAM part. Note that this driver expects the Write Protect (/WP) and /Hold pins are pulled high (i.e. inactive).
//
// History
// 2019-04-25 by Tamkin Rahman
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "drivers/mss_gpio/mss_gpio.h"

#include "drivers/device/memory/mr2xh40_mram.h"

#include <stdlib.h> // Used to include a definition of NULL.

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ENUMERATIONS AND ENUMERATION TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

// Enum used to hold the command bytes for the part. All SPI transactions should start with a command byte.
typedef enum
{
	MRAM_CMD_WREN  = 0x06, // Write enable
	MRAM_CMD_WRDI  = 0x04, // Write disable
	MRAM_CMD_RDSR  = 0x05, // Read status register
	MRAM_CMD_WRSR  = 0x01, // Write status register
	MRAM_CMD_READ  = 0x03, // Read data bytes
	MRAM_CMD_WRITE = 0x02, // Write data bytes
	MRAM_CMD_SLEEP = 0xB9, // Enter sleep mode
	MRAM_CMD_WAKE  = 0xAB  // Exit sleep mode
} MRAMCmdBytes_t;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Sends a single command without any bytes afterwards. This is useful for certain commands that don't require any data after the initial command byte.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static void mr2xh40_single_cmd(
    MRAMInstance_t * mram,  // The MRAM instance to send the command to.
    uint8_t cmd             // The command byte to send.
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void mr2xh40_init(MRAMInstance_t * mram)
{
	// Note that the datasheet specifies up to a 40 MHz clock rate.
	//spi_configure_slave(mram->core, mram->slave, SPI_MODE_MASTER, SPI_MODE3, PCLK_DIV_32);
	spi_configure_gpio_ss(mram->cs_pin);
	MSS_GPIO_config(MSS_GPIO_10, MSS_GPIO_OUTPUT_MODE);
	MSS_GPIO_config(MSS_GPIO_11, MSS_GPIO_OUTPUT_MODE);
	MSS_GPIO_set_output(MSS_GPIO_10, 1);
	MSS_GPIO_set_output(MSS_GPIO_11, 1);

	//Enable writes so we can write status reg.
		mr2xh40_single_cmd(mram, MRAM_CMD_WREN);

	//Prepare command: write status reg, with value 0.
	uint8_t cmd[2] = { MRAM_CMD_WRSR,
						0};

	spi_transaction_block_write_without_toggle(
					mram->core,
					mram->slave,
					&cmd,
					2,
					NULL,
					0);

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void mr2xh40_read_status_register(MRAMInstance_t * mram, uint8_t * buffer)
{
	uint8_t cmd = MRAM_CMD_RDSR;
	spi_transaction_block_read_without_toggle(
				mram->core,
				mram->slave,
				&cmd,
				1,
				buffer,
				1);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void mr2xh40_read(MRAMInstance_t * mram, uint32_t address, uint8_t * rd_buffer, size_t rd_buffer_size)
{
	uint8_t cmd[4] = { MRAM_CMD_READ,
					  (address >> 16) & 0x07,
					  (address >> 8) & 0xFF,
					  (address) & 0xFF
	};
	spi_transaction_block_read_without_toggle(
					mram->core,
					mram->slave,

					cmd,
					sizeof(cmd),
					rd_buffer,
					rd_buffer_size);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void mr2xh40_write(MRAMInstance_t * mram, uint32_t address, uint8_t * wr_buffer, size_t wr_buffer_size)
{
	uint8_t cmd[4] = { MRAM_CMD_WRITE,
					  (address >> 16) & 0x07,
					  (address >> 8) & 0xFF,
					  (address) & 0xFF
	};
	mr2xh40_single_cmd(mram, MRAM_CMD_WREN); // Enable writes.
//	uint8_t stat_reg = 0xA5;
//	mr2xh40_read_status_register(mram, &stat_reg);

	spi_transaction_block_write_without_toggle(
					mram->core,
					mram->slave,
					cmd,
					sizeof(cmd),
					wr_buffer,
					wr_buffer_size);

	mr2xh40_single_cmd(mram, MRAM_CMD_WRDI); // Disable writes.
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static void mr2xh40_single_cmd(MRAMInstance_t * mram, uint8_t cmd)
{
    spi_transaction_block_read_without_toggle(
       mram->core,
       mram->slave,
       &cmd,
       1,
       NULL,
       0);
}
