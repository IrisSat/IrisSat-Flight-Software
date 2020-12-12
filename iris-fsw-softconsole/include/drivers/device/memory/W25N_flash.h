#ifndef W25N_FLASH_H
#define W25N_FLASH_H
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  External flash memory (W25N01GVxxIG) functions and definitions.
//	This driver is a modified version of the Mongoose OS Winbond W25XXX SPI NAND Flash Driver
//	https://github.com/mongoose-os-libs/vfs-dev-w25xxx
//
// History
// 2019-04-17 by Joseph Howarth
// - Created.
// 2020-03-31 by Joseph Howarth
// - Updated to use flash interface.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 * Copyright (c) 2014-2018 Cesanta Software Limited
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "drivers/device/memory/flash_common.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


#define W25N_PAGE_SIZE 2048U
#define W25N_BLOCK_SIZE (64 * W25N_PAGE_SIZE)
#define W25N_DIE_SIZE (1024 * W25N_BLOCK_SIZE)

#define W25N_REG_CONF_BUF (1 << 3)
#define W25N_REG_CONF_ECCE (1 << 4)

#define W25N_REG_STAT_BUSY (1 << 0)
#define W25N_REG_STAT_WEL (1 << 1)
#define W25N_REG_STAT_EFAIL (1 << 2)
#define W25N_REG_STAT_PFAIL (1 << 3)
#define W25N_REG_STAT_ECC0 (1 << 4)
#define W25N_REG_STAT_ECC1 (1 << 5)
#define W25N_REG_STAT_LUTF (1 << 6)

#define W25N_ID_1	0xEF
#define W25N_ID_2	0xAA
#define W25N_ID_3	0x21

#define W25N_BB_LUT_SIZE 20

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ENUMS AND ENUM TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef enum  {

  W25N_OP_RST = 0xff,
  W25NXX_OP_DIE_SELECT = 0xc2,
  W25N_OP_READ_JEDEC_ID = 0x9f,
  W25N_OP_READ_REG = 0x05,
  W25N_OP_WRITE_REG = 0x01,
  W25N_OP_WRITE_ENABLE = 0x06,
  W25N_OP_WRITE_DISABLE = 0x04,
  W25N_OP_BBM_SWAP_BLOCKS = 0xa1,
  W25N_OP_BBM_READ_LUT = 0xa5,
  W25N_OP_BBM_READ_LAST_ECC_FAIL_ADDR = 0xa9,
  W25N_OP_PROG_DATA_LOAD = 0x02,
  W25N_OP_PROG_RAND_DATA_LOAD = 0x84,
  W25N_OP_PROG_EXECUTE = 0x10,
  W25N_OP_BLOCK_ERASE = 0xd8,
  W25N_OP_PAGE_DATA_READ = 0x13,
  W25N_OP_READ = 0x03,

} W25NOperation_t;

typedef enum  {

  W25N_REG_PROT = 0xa0, /* Protection register */
  W25N_REG_CONF = 0xb0, /* Configuration register */
  W25N_REG_STAT = 0xc0, /* Status register */

} W25NReg_t;


typedef enum{

	ECC_OFF,
	ECC_ON
} W25NEccCheck_t;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTS AND STRUCT TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct  {
  uint32_t invalid : 1;
  uint32_t enable : 1;
  uint16_t lba : 10;
  uint16_t pba;
} W25NBadBlockEntry_t;

typedef struct  {

  W25NBadBlockEntry_t e[W25N_BB_LUT_SIZE];

} W25NBadBlockLUT_t;

typedef struct  {

  void (*spi_write)(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *wr_buffer,uint16_t wr_size);
  void (*spi_read)(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *rd_buffer,uint16_t rd_size);

  size_t size;
  W25NBadBlockLUT_t bb_lut;
  uint32_t bb_reserve : 8; /* # of blocks to reserve at the end of each die. */
  uint32_t ecc_chk : 1;    /* Check ECC when reading. */



}W25NDevice_t;



//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function initializes the flash memory. It populates the FlashDevice struct,
//	and verifies that the device ID can be read and is correct.
//
// Parameters:
//
//	dev:			This should be a pointer to a FLASH_dev struct, which will be
//					used to refer to the device.
//
//	spi:			This should be the spi instance used.
//					This should already be initialized.
//
//  ss_pin: 		This parameter should be the pin used as the slave select.
//					This should already be initialized, by calling the spi_configure_gpio_ss()
//					function from the spi driver.
//
//	bb_reserve:		This should be the number of blocks to reserve? Or the number of bad blocks?
//
//	ecc_check:		This selects if the error correcting code (ecc) is used.
//
// Returns:
//  Returns FLASH_OK if the flash memory id is successfully read.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//Add part in detect(), where the die is put into buffered read, unprotect and read bb lut.
FlashStatus_t w25n_dev_init(W25NDevice_t * dev, uint8_t bb_reserve, W25NEccCheck_t ecc_check);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function writes to the flash memory.
//
// Parameters:
//
//	dev:			This should be a pointer to a FLASH_dev struct, which will be
//					used to refer to the device.
//
//	address:		The address to start writing from.
//
//  len: 			The number of bytes to write.
//
//	dst:			A pointer to the src data.
//
//
// Returns:
//  Returns FLASH OK if the read is successful.
//	Returns FLASH_INVALID if an improper address is used.
//	Returns FLASH_ERROR if there is a different error.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t w25n_write(W25NDevice_t *dd,size_t address, size_t len,const void *src);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function reads from the flash memory.
//
// Parameters:
//
//	dev:			This should be a pointer to a FLASH_dev struct, which will be
//					used to refer to the device.
//
//	address:		The address to start reading from.
//
//  len: 			The number of bytes to read.
//
//	dst:			A pointer to where the read bytes will be stored.
//
//
// Returns:
//  Returns FLASH OK if the read is successful.
//	Returns FLASH_INVALID if an improper address is used.
//	Returns FLASH_ERROR if there is a different error.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t w25n_read(W25NDevice_t *dev, size_t address, size_t len, void *dst);


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function erases the flash memory.
//
// Parameters:
//
//	dev:			This should be a pointer to a FLASH_dev struct, which will be
//					used to refer to the device.
//
//	block_num:		The block to start erasing from.
//
//  num_blocks: 	The number of blocks to erase.
//
//
// Returns:
//  Returns FLASH OK if the read is successful.
//	Returns FLASH_INVALID if an improper address is used.
//	Returns FLASH_ERROR if there is a different error.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t w25n_erase_blocks(W25NDevice_t *dd, size_t block_num, size_t num_blocks);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This reads the bad block management lookup table.
//
// Parameters:
//
//	dev:			This should be a pointer to a FLASH_dev struct, which will be
//					used to refer to the device.
//
//	lut:			A pointer to the look up table where the results will be stored,
//
//  num_bb: 		The number of bad blocks will be put here.
//
//
// Returns:
//  Returns FLASH OK if the read is successful.
//	Returns FLASH_ERROR if there is an error.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t w25n_read_bb_lut(W25NDevice_t *dd,W25NBadBlockLUT_t *lut, int *num_bb);


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This adds a mapping to the bad block lookup table.
//
// Parameters:
//
//	dev:			This should be a pointer to a FLASH_dev struct, which will be
//					used to refer to the device.
//
//	bad_off:		The block address containing this address will be re-mapped to the block containing good_off
//
//  good_off: 		The block memory containing this address will be re-mapped to the block address containing bad_off.
//
//
// Returns:
//  Returns FLASH OK if the read is successful.
//	Returns FLASH_ERROR if there is an error.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t w25n_remap_block(W25NDevice_t *dd, size_t bad_off,size_t good_off);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the whole device.
//
// Parameters:
//
//	dev:			This should be a pointer to a FLASH_dev struct, which will be
//					used to refer to the device.
//
//
//
// Returns:
//  Returns FLASH OK if the read is successful.
//	Returns FLASH_ERROR if there is an error.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t w25n_erase_device(W25NDevice_t *dd);
//TODO: Implement this function!.

#endif // FLASH_H
