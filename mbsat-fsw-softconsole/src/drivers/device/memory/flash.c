//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//  Github: https://github.com/joehowarth17/ManitobaSat-Flight-Software
//
// File Description:
//  External flash memory (MT25Q) driver.
//
// History
// 2020-03-13 by Joseph Howarth
// - Created.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "flash.h"
#include "spi.h"
#include "board_definitions.h"
#include "FreeRTOS.h"
#include "task.h"

#define STAT_POLLING_RATE   100
#define M25Q_ID 0x20
#define FLASH_STAT_IS_BUSY(x)       (~((x>>7)&0x01))   //Gets the busy bit from status register byte. 1 if busy, 0 if ready.
#define FLASH_STAT_ERASE_FAILED(x)     ((x>>5)&0x01)   //Gets the erase bit from status register byte. 0 if ok, 1 if failure.
#define FLASH_STAT_WRITE_FAILED(x)     ((x>>4)&0x01)   //Gets the write bit from status register byte. 0 if ok, 1 if failure.
#define FLASH_STAT_GET_ADRESS_MODE(x)  ((x)&0x01)      //Gets the addressing bit from status register byte. 0 if 3-byte, 1 if 4-byte.




//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This checks device ID, disables protected areas, and puts the flash device into 4 byte address mode.
//  Returns FLASH_OK on success.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_setup_flash(){

    FlashStatus_t result = FLASH_OK;

    //Check that the id of the flash memory is correct.
    uint8_t command = FLASH_OP_READ_ID;
    uint8_t flash_id = 0;
    spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &command, 1, &flash_id, 1);

    if(flash_id!= M25Q_ID){
        result = FLASH_INVALID_ID;
    }

    if(result == FLASH_OK){
        //Put the device into 4-byte address mode.
        command = FLASH_OP_ENABLE_4_BYTE_MODE;
        spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &command, 1,0,0);

        while(MT25Q_flash_is_busy() == FLASH_BUSY){
            if(xTaskGetSchedulerState() == taskSCHEDULER_RUNNING){
                vTaskDelay(pdMS_TO_TICKS(STAT_POLLING_RATE));
            }
        }
        //Verify that 4-byte mode is enabled.
        command = FLASH_OP_READ_STAT_REG;
        uint8_t stat_reg = 0;
        spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &command, 1, &stat_reg, 1);

        if(FLASH_STAT_GET_ADRESS_MODE(stat_reg) != 1){
            result = FLASH_ERROR_ADRESSING_MODE;
        }
    }
    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This writes data to the flash memory starting at the given address. The write
//  address will wrap around at the page boundary (256 bytes). This function is non-blocking,
//  and will return FLASH_BUSY if the previous operation is not finished. If the write is successful,
// the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_write_page(uint32_t addr, uint8_t* data,uint32_t size){

    FlashStatus_t result = FLASH_OK;

    uint8_t wp_command = FLASH_OP_WRITE_ENABLE;
    spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &wp_command, sizeof(wp_command), 0, 0);



    uint8_t wr_command [5] = {FLASH_OP_PROGRAM,
                            (addr>>24)&0xFF,
                            (addr>>16)&0xFF,
                            (addr>>8)&0xFF,
                            (addr)&0xFF,
                            };

    spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, wr_command, sizeof(wr_command), data, size);

        return result;

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This reads data from the flash memory starting at the given address.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_read(uint32_t addr, uint8_t* data,uint32_t size){

    uint8_t command [5] = {FLASH_OP_READ,
                            (addr>>24)&0xFF,
                            (addr>>16)&0xFF,
                            (addr>>8)&0xFF,
                            (addr)&0xFF,
                            };

    spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, command, sizeof(command), data, size);

        return FLASH_OK;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the whole memory. This function is non-blocking,
//  and will return FLASH_BUSY if the previous operation is not finished.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_device(){

	FlashStatus_t result = FLASH_OK;

	uint8_t wp_command = FLASH_OP_WRITE_ENABLE;
	spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &wp_command, sizeof(wp_command),0,0);

	uint8_t command[5] = {FLASH_OP_ERASE_DIE,0,0,0,0};
	spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, command, sizeof(command),0,0);

	uint8_t check_command = FLASH_OP_READ_FLAG_REG;
	uint8_t flag_reg = 0;
	spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &check_command, 1, &flag_reg, 1);

	//Wait until the erase is done.
	while(FLASH_STAT_IS_BUSY(flag_reg)){
		vTaskDelay(pdMS_TO_TICKS(200));
		spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &check_command, 1, &flag_reg, 1);
	}

	if(FLASH_STAT_ERASE_FAILED(flag_reg)){
		result = FLASH_ERASE_ERROR;
		uint8_t clear_flag_command = FLASH_OP_CLEAR_FLAG_REG;
		spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &clear_flag_command, sizeof(clear_flag_command),0,0);
	}


	return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the 64k sector containing the given address.This function is non-blocking,
//  and will return FLASH_BUSY if the previous operation is not finished. If the erase is successful,
// the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_64k(uint32_t addr){
	FlashStatus_t result = FLASH_OK;

	uint8_t wp_command = FLASH_OP_WRITE_ENABLE;
	spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &wp_command, sizeof(wp_command),0,0);

	uint8_t command[5] = {	FLASH_OP_ERASE_DIE,
							(addr>>24) & 0xFF,
							(addr>>16) & 0xFF,
							(addr>>8) & 0xFF,
							(addr) & 0xFF};

	spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, command, sizeof(command),0,0);

	uint8_t check_command = FLASH_OP_READ_FLAG_REG;
	uint8_t flag_reg = 0;
	spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &check_command, 1, &flag_reg, 1);

	//Wait until the erase is done.
	while(FLASH_STAT_IS_BUSY(flag_reg)){
		vTaskDelay(pdMS_TO_TICKS(200));
		spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &check_command, 1, &flag_reg, 1);
	}

	if(FLASH_STAT_ERASE_FAILED(flag_reg)){
		result = FLASH_ERASE_ERROR;
		uint8_t clear_flag_command = FLASH_OP_CLEAR_FLAG_REG;
		spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &clear_flag_command, sizeof(clear_flag_command),0,0);
	}


	return result;

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the 32k sector containing the given address.This function is non-blocking,
//  and will return FLASH_BUSY if the previous operation is not finished. If the erase is successful,
// the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_32k(uint32_t addr){

	FlashStatus_t result = FLASH_OK;

	uint8_t wp_command = FLASH_OP_WRITE_ENABLE;
	spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &wp_command, sizeof(wp_command),0,0);

	uint8_t command[5] = {	FLASH_OP_ERASE_DIE,
							(addr>>24) & 0xFF,
							(addr>>16) & 0xFF,
							(addr>>8) & 0xFF,
							(addr) & 0xFF};

	spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, command, sizeof(command),0,0);

	uint8_t check_command = FLASH_OP_READ_FLAG_REG;
	uint8_t flag_reg = 0;
	spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &check_command, 1, &flag_reg, 1);

	//Wait until the erase is done.
	while(FLASH_STAT_IS_BUSY(flag_reg)){
		vTaskDelay(pdMS_TO_TICKS(200));
		spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &check_command, 1, &flag_reg, 1);
	}

	if(FLASH_STAT_ERASE_FAILED(flag_reg)){
		result = FLASH_ERASE_ERROR;
		uint8_t clear_flag_command = FLASH_OP_CLEAR_FLAG_REG;
		spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &clear_flag_command, sizeof(clear_flag_command),0,0);
	}


	return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the 4k sector containing the given address.This function is non-blocking,
//  and will return FLASH_BUSY if the previous operation is not finished. If the erase is successful,
// the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_4k(uint32_t addr){

	FlashStatus_t result = FLASH_OK;

	uint8_t wp_command = FLASH_OP_WRITE_ENABLE;
	spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &wp_command, sizeof(wp_command),0,0);

	uint8_t command[5] = {	FLASH_OP_ERASE_DIE,
							(addr>>24) & 0xFF,
							(addr>>16) & 0xFF,
							(addr>>8) & 0xFF,
							(addr) & 0xFF};

	spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, command, sizeof(command),0,0);

	uint8_t check_command = FLASH_OP_READ_FLAG_REG;
	uint8_t flag_reg = 0;
	spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &check_command, 1, &flag_reg, 1);

	//Wait until the erase is done.
	while(FLASH_STAT_IS_BUSY(flag_reg)){
		vTaskDelay(pdMS_TO_TICKS(200));
		spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &check_command, 1, &flag_reg, 1);
	}

	if(FLASH_STAT_ERASE_FAILED(flag_reg)){
		result = FLASH_ERASE_ERROR;
		uint8_t clear_flag_command = FLASH_OP_CLEAR_FLAG_REG;
		spi_transaction_block_write_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &clear_flag_command, sizeof(clear_flag_command),0,0);
	}


	return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This checks if there is a write status register, program or erase operation in
//  progress. Returns FLASH_BUSY or FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_is_busy(){

    FlashStatus_t result = FLASH_OK;
    uint8_t command = FLASH_OP_READ_STAT_REG;
    uint8_t stat_reg = 0;
    spi_transaction_block_read_without_toggle(FLASH_SPI_CORE, FLASH_SLAVE_CORE, FLASH_SS_PIN, &command, 1, &stat_reg, 1);

    if(FLASH_STAT_IS_BUSY(stat_reg)){
        result = FLASH_BUSY;
    }

    return result;
}
