//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  Common interface for external flash drivers.
//
// History
// 2020-03-30 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "drivers/device/memory/flash_common.h"
#include "drivers/device/memory/W25N_flash.h"
#include "drivers/device/memory/MT25Q_flash.h"
#include "drivers/device/memory/AT25SF_flash.h"
#include "drivers/device/memory/W25Q_flash.h"
#include "drivers/protocol/spi.h"
#include "board_definitions.h"

//Device specific spi functions
void data_flash_spi_read(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *rd_buffer,uint16_t rd_size);
void data_flash_spi_write(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *wr_buffer,uint16_t wr_size);

void program_flash_spi_read(uint8_t *cmd_buffer, uint16_t cmd_size, uint8_t *rd_buffer, uint16_t rd_size);
void program_flash_spi_write(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *wr_buffer,uint16_t wr_size);

//static W25NDevice_t data_flash_driver;
//static MT25Q_Device_t data_flash_driver = {	.spi_read = data_flash_spi_read,
//											.spi_write=data_flash_spi_write,
//											.num_dies =2,
//											.size = 2*MT25Q_DIE_SIZE};

static W25NDevice_t data_flash_driver = {	.spi_read = data_flash_spi_read,
											.spi_write=data_flash_spi_write,
											.size = 1*W25N_DIE_SIZE};

static FlashDev_t 	data_flash = {	.driver = &data_flash_driver,
									.id = DATA_FLASH,
									.page_size = W25N_PAGE_SIZE,
									.erase_size = W25N_BLOCK_SIZE,
									.device_size = 1*W25N_DIE_SIZE	};

////static W25NDevice_t data_flash_driver;
//static AT25SF_Device_t program_flash_driver = {	.spi_read = program_flash_spi_read,
//												.spi_write= program_flash_spi_write};
static W25Q_Device_t program_flash_driver = {   .spi_read = program_flash_spi_read,
                                              .spi_write= program_flash_spi_write};


static FlashDev_t 	program_flash = {	.driver = &program_flash_driver,
										.id = PROGRAM_FLASH,
										.page_size = W25Q_PAGE_SIZE,
										.erase_size = W25Q_SUBSECTOR_SMALL_SIZE,
										.device_size = W25Q_DIE_SIZE	};

FlashDev_t *flash_devices[NUM_FLASH_DEVICES] = {
		&data_flash,
		&program_flash
};


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t flash_device_init(FlashDev_t *device){
	FlashStatus_t result = FLASH_ERROR;
	switch(device->id){

		case DATA_FLASH:
			result = w25n_dev_init(device->driver, 8, ECC_ON);
//			result = MT25Q_setup_flash(device->driver);
		break;

		case PROGRAM_FLASH:
//			result = AT25SF_setup_flash(device->driver);
		    result = W25Q_setup_flash(device->driver);
		break;
	}
	return result;
}

FlashStatus_t flash_write(FlashDev_t *device,uint32_t address, uint8_t *wr_buffer,uint32_t wr_size){

	FlashStatus_t result = FLASH_ERROR;
	switch(device->id){

		case DATA_FLASH:
			result = w25n_write(device->driver,address,wr_size,wr_buffer);
//			result = MT25Q_flash_write_page(device->driver, address, wr_buffer, wr_size);
		break;

		case PROGRAM_FLASH:;
//			result = AT25SF_flash_write_page(device->driver, address, wr_buffer, wr_size);
			result = W25Q_flash_write_page(device->driver, address, wr_buffer, wr_size);
		break;

	}
	return result;
}

FlashStatus_t flash_read(FlashDev_t *device, uint32_t address, uint8_t *rd_buffer,uint32_t rd_size){

	FlashStatus_t result = FLASH_ERROR;
	switch(device->id){

		case DATA_FLASH:
			result = w25n_read(device->driver,address,rd_size,rd_buffer);
//			result = MT25Q_flash_read(device->driver, address, rd_buffer, rd_size);
		break;

		case PROGRAM_FLASH:;
			result = W25Q_flash_read(device->driver, address, rd_buffer, rd_size);
//			result = AT25SF_flash_read(device->driver, address, rd_buffer, rd_size);

		break;

	}
	return result;
}

FlashStatus_t flash_erase(FlashDev_t *device, uint32_t address){

	FlashStatus_t result = FLASH_ERROR;
	switch(device->id){

		case DATA_FLASH: ;
			uint32_t blocknum = address/W25N_BLOCK_SIZE;
			result = w25n_erase_blocks(device->driver,blocknum,1);
//		result = MT25Q_flash_erase_4k(device->driver, address);
		break;

		case PROGRAM_FLASH:;
//			result = AT25SF_flash_erase_4k(device->driver, address);
			result = W25Q_flash_erase_4k(device->driver, address);
		break;
	}
	return result;
}

FlashStatus_t flash_erase_device(FlashDev_t *device){

	FlashStatus_t result = FLASH_ERROR;
	switch(device->id){

		case DATA_FLASH:;
			uint32_t numblocks = W25N_DIE_SIZE/W25N_BLOCK_SIZE -8;
			result = w25n_erase_blocks(device->driver,0,numblocks);
//			result = MT25Q_flash_erase_device(device->driver);
		break;

		case PROGRAM_FLASH:;
//			result = AT25SF_flash_erase_device(device->driver);
			result = W25Q_flash_erase_device(device->driver);
		break;

	}
	return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEVICE SPECIFIC FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//These are used so that we can easily modify the basic spi functions used for each driver.
//Each Flash driver ultimately just does spi read and spi write, so we write the drivers to use these functions.
//This makes it so we only have to change these in one place instead of all across the flash drivers.


void data_flash_spi_read(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *rd_buffer,uint16_t rd_size){
	spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE,  cmd_buffer, cmd_size, rd_buffer, rd_size);
}
void data_flash_spi_write(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *wr_buffer,uint16_t wr_size){
	spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE,  cmd_buffer, cmd_size, wr_buffer, wr_size);
}

void program_flash_spi_read(uint8_t *cmd_buffer, uint16_t cmd_size, uint8_t *rd_buffer, uint16_t rd_size){

    spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, cmd_buffer, cmd_size, rd_buffer, rd_size);

}
void program_flash_spi_write(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *wr_buffer,uint16_t wr_size){

    spi_transaction_block_write_without_toggle(PROGRAM_FLASH_SPI_CORE, FLASH_SLAVE_CORE, cmd_buffer, cmd_size, wr_buffer, wr_size);
}
