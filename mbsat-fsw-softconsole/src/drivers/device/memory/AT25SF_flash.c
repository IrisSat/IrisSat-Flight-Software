//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//	Github: https://github.com/joehowarth17/ManitobaSat-Flight-Software
//
// File Description:
//  Dev Kit on-board flash memory (AT25SF161) functions and definitions.
//
// History
// 2020-05-04 by Joseph Howarth
// - Created.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "AT25SF_flash.h"
#include "FreeRTOS.h"
#include "task.h"
#include "board_definitions.h"
#include "mss_spi.h"

//Returns 1 if device is busy, 0 if not.
uint8_t AT25SF_is_busy(AT25SF_Device_t * dev);

FlashStatus_t AT25SF_setup_flash(AT25SF_Device_t * dev){

	FlashStatus_t result = FLASH_OK;

	//Set up SPI driver.
	MSS_SPI_init(&g_mss_spi0);

	//Clock div of 256 to get 250khz SPI clock rate.
	MSS_SPI_configure_master_mode(&g_mss_spi0,MSS_SPI_SLAVE_0,MSS_SPI_MODE0,256,MSS_SPI_BLOCK_TRANSFER_FRAME_SIZE);



	//Init GPIO
	 MSS_GPIO_config( PROGRAM_FLASH_WP_PIN, MSS_GPIO_OUTPUT_MODE );
	 MSS_GPIO_config( PROGRAM_FLASH_HOLD_PIN, MSS_GPIO_OUTPUT_MODE );

	//set gpio high
	 MSS_GPIO_set_output(PROGRAM_FLASH_WP_PIN, 1);
	 MSS_GPIO_set_output(PROGRAM_FLASH_HOLD_PIN, 1);

	 uint8_t command = AT25SF_OP_READ_ID;

	uint8_t id[3] = {0};
	dev->spi_read(&command, sizeof(command),id,sizeof(id));

	if((id[0] != AT25SF_ID_BYTE1) && (id[1] != AT25SF_ID_BYTE2) && (id[2] != AT25SF_ID_BYTE3)){
		result = FLASH_INVALID_ID;
	}

	return result;
}

FlashStatus_t AT25SF_flash_write_page(AT25SF_Device_t * dev,uint32_t addr, uint8_t* data,uint32_t size){

	if(addr>AT25SF_DIE_SIZE) return FLASH_INVALID_ADDRESS;

	uint8_t we_command = AT25SF_OP_WRITE_ENABLE;
	dev->spi_write(&we_command,sizeof(we_command),NULL,0);

	uint8_t command [4] = {	AT25SF_OP_PROGRAM,
							(addr>>16) & 0xFF,
							(addr>>8)  & 0xFF,
							(addr)	   & 0xFF
							};

	dev->spi_write(command,sizeof(command),data,size);

	while(AT25SF_is_busy(dev)){
        if(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING){
            vTaskDelay(pdMS_TO_TICKS(100));
        }
	}

	return FLASH_OK;
}

FlashStatus_t AT25SF_flash_read(AT25SF_Device_t * dev,uint32_t addr, uint8_t* data,uint32_t size){

	if(addr > AT25SF_DIE_SIZE) return FLASH_INVALID_ADDRESS;

	// Using the 0x0B command results in one dummy byte clocked after the
	// command, so we added a 0 to the command, so that the dummy byte is not
	// added to the data output.

		uint8_t command [5] = {	AT25SF_OP_READ,
								(addr>>16) & (0xFF),
								(addr>>8)  & (0xFF),
								(addr)	   & (0xFF),
								0x00
								};

		dev->spi_read(command, sizeof(command),data,size);



	return FLASH_OK;
}

FlashStatus_t AT25SF_flash_erase_device(AT25SF_Device_t * dev){

	uint8_t we_command = AT25SF_OP_WRITE_ENABLE;
	dev->spi_write(&we_command,sizeof(we_command),NULL,0);

	uint8_t command = AT25SF_OP_ERASE_DIE;

	dev->spi_write(&command,sizeof(command),NULL,0);

	while(AT25SF_is_busy(dev)){
        if(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING){
            vTaskDelay(pdMS_TO_TICKS(100));
        }
	}

	return FLASH_OK;
}

FlashStatus_t AT25SF_flash_erase_4k(AT25SF_Device_t * dev,uint32_t addr){

	if(addr>AT25SF_DIE_SIZE) return FLASH_INVALID_ADDRESS;

	uint8_t we_command = AT25SF_OP_WRITE_ENABLE;
	dev->spi_write(&we_command,sizeof(we_command),NULL,0);

	uint8_t command [4] = {	AT25SF_OP_ERASE_SECTOR_4k,
							(addr>>16) & 0xFF,
							(addr>>8)  & 0xFF,
							(addr)	   & 0xFF
							};

	dev->spi_write(command,sizeof(command),NULL,0);

	while(AT25SF_is_busy(dev)){
        if(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING){
            vTaskDelay(pdMS_TO_TICKS(100));
        }
	}

	return FLASH_OK;
}

uint8_t AT25SF_is_busy(AT25SF_Device_t * dev){

	uint8_t result = 0;
	uint8_t stat_reg = 0;
	uint8_t command = AT25SF_OP_READ_STAT_REG_1;

	dev->spi_read(&command,sizeof(command),&stat_reg,sizeof(stat_reg));

	result = stat_reg & 0x01;	//Bit 0 of the  status register byte 1 is the ready/busy status.

	return result;
}
