#ifndef FLASH_H
#define FLASH_H
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// Repository:
//	Github: https://github.com/UMSATS/cdh-tsat5
//
// File Description:
//  External flash memory (W25N01GVxxIG) functions and definitions.
//	This driver is a modified version of the Mongoose OS Winbond W25XXX SPI NAND Flash Driver
//	https://github.com/mongoose-os-libs/vfs-dev-w25xxx
//
// History
// 2019-04-17 by Joseph Howarth
// - Created.
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
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "spi.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


#define FLASH_PAGE_SIZE 2048U
#define FLASH_BLOCK_SIZE (64 * FLASH_PAGE_SIZE)
#define FLASH_DIE_SIZE (1024 * FLASH_BLOCK_SIZE)

#define FLASH_REG_CONF_BUF (1 << 3)
#define FLASH_REG_CONF_ECCE (1 << 4)

#define FLASH_REG_STAT_BUSY (1 << 0)
#define FLASH_REG_STAT_WEL (1 << 1)
#define FLASH_REG_STAT_EFAIL (1 << 2)
#define FLASH_REG_STAT_PFAIL (1 << 3)
#define FLASH_REG_STAT_ECC0 (1 << 4)
#define FLASH_REG_STAT_ECC1 (1 << 5)
#define FLASH_REG_STAT_LUTF (1 << 6)

#define FLASH_ID_1	0xEF
#define FLASH_ID_2	0xAA
#define FLASH_ID_3	0x21

#define FLASH_BB_LUT_SIZE 20

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ENUMS AND ENUM TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef enum  {

  FLASH_OP_RST = 0xff,
  W25MXX_OP_DIE_SELECT = 0xc2,
  FLASH_OP_READ_JEDEC_ID = 0x9f,
  FLASH_OP_READ_REG = 0x05,
  FLASH_OP_WRITE_REG = 0x01,
  FLASH_OP_WRITE_ENABLE = 0x06,
  FLASH_OP_WRITE_DISABLE = 0x04,
  FLASH_OP_BBM_SWAP_BLOCKS = 0xa1,
  FLASH_OP_BBM_READ_LUT = 0xa5,
  FLASH_OP_BBM_READ_LAST_ECC_FAIL_ADDR = 0xa9,
  FLASH_OP_PROG_DATA_LOAD = 0x02,
  FLASH_OP_PROG_RAND_DATA_LOAD = 0x84,
  FLASH_OP_PROG_EXECUTE = 0x10,
  FLASH_OP_BLOCK_ERASE = 0xd8,
  FLASH_OP_PAGE_DATA_READ = 0x13,
  FLASH_OP_READ = 0x03,

} FlashOperation_t;

typedef enum  {

  FLASH_REG_PROT = 0xa0, /* Protection register */
  FLASH_REG_CONF = 0xb0, /* Configuration register */
  FLASH_REG_STAT = 0xc0, /* Status register */

} FlashReg_t;

typedef enum{

	FLASH_OK,
	FLASH_ERROR,
	FLASH_INVALID,
	FLASH_READ_ERROR_SINGLE,
	FLASH_READ_ERROR_MULTI

} FlashStatus_t;

typedef enum{

	ECC_OFF,
	ECC_ON
} EccCheck_t;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTS AND STRUCT TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct  {
  uint32_t invalid : 1;
  uint32_t enable : 1;
  uint16_t lba : 10;
  uint16_t pba;
} FlashBadBlockEntry_t;

typedef struct  {

  FlashBadBlockEntry_t e[FLASH_BB_LUT_SIZE];

} FlashBadBlockLUT_t;

typedef struct  {

  CoreSPIInstance_t spi;
  mss_gpio_id_t ss_port_id;	/* Slave select GPIO pin */

  size_t size;
  FlashBadBlockLUT_t bb_lut;
  uint32_t bb_reserve : 8; /* # of blocks to reserve at the end of each die. */
  uint32_t ecc_chk : 1;    /* Check ECC when reading. */



}FlashDevice_t;



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
FlashStatus_t flash_dev_init(FlashDevice_t * dev,CoreSPIInstance_t spi, mss_gpio_id_t ss_pin, uint8_t bb_reserve, EccCheck_t ecc_check);

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
FlashStatus_t flash_write_(FlashDevice_t *dd,size_t address, size_t len,const void *src);

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
FlashStatus_t flash_read(FlashDevice_t *dev, size_t address, size_t len, void *dst);


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
FlashStatus_t flash_erase_blocks(FlashDevice_t *dd, size_t block_num, size_t num_blocks);

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
FlashStatus_t flash_read_bb_lut(FlashDevice_t *dd,FlashBadBlockLUT_t *lut, int *num_bb);


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
FlashStatus_t flash_remap_block(FlashDevice_t *dd, size_t bad_off,size_t good_off);

#endif // FLASH_H
