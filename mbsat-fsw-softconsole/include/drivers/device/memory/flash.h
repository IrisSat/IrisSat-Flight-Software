#ifndef FLASH_H
#define FLASH_H
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//	Github: https://github.com/joehowarth17/ManitobaSat-Flight-Software
//
// File Description:
//  External flash memory (MT25Q) functions and definitions.
//
// History
// 2020-03-07 by Joseph Howarth
// - Created.
//
// MT25Q has 256 byte pages
//           64k/32k/4k byte sectors
//			 512Mb dies.
// This driver uses 4-byte addressing mode.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdint.h>

#define FLASH_PAGE_SIZE             256
#define FLASH_SUBSECTOR_SMALL_SIZE  4096
#define FLASH_SUBSECTOR_LARGE_SIZE  32768
#define FLASH_SECTOR_SIZE           65536
#define FLASH_DIE_SIZE              (0x4000000)
#define FLASH_SIZE                  (0x8000000)
typedef enum  {

  FLASH_OP_RST_EN = 0x66,
  FLASH_OP_RST = 0x99,

  FLASH_OP_READ_ID = 0xAF,

  FLASH_OP_READ_STAT_REG = 0x05,
  FLASH_OP_WRITE_STAT_REG = 0x01,

  FLASH_OP_READ_FLAG_REG = 0x70,
  FLASH_OP_CLEAR_FLAG_REG =0x50,

  FLASH_OP_READ_EXT_REG = 0xC8,	//Read Extended Addressing mode register.
  FLASH_OP_WRITE_EXT_REG = 0xC5,

  FLASH_OP_READ_DEFAULT_CONFIG = 0x85,
  FLASH_OP_WRITE_DEFAULT_CONFIG = 0xB1,

  FLASH_OP_ENABLE_4_BYTE_MODE = 0xB7,

  FLASH_OP_WRITE_SECTOR_PROTECTION = 0x2C,
  FLASH_OP_READ_PASSWORD = 0x27,

  FLASH_OP_WRITE_ENABLE = 0x06,
  FLASH_OP_WRITE_DISABLE = 0x04,

  FLASH_OP_READ = 0x13,	// This is for 4-byte addressing.
  FLASH_OP_PROGRAM  = 0x12,
  FLASH_OP_ERASE_DIE = 0xC4,
  FLASH_OP_ERASE_SECTOR_64k = 0xDC,
  FLASH_OP_ERASE_SECTOR_32k = 0x5C,
  FLASH_OP_ERASE_SECTOR_4k = 0x21,

} FlashOperation_t;

typedef enum{

	FLASH_OK,
	FLASH_BUSY,
	FLASH_ERROR,
	FLASH_INVALID_ID,
	FLASH_INVALID_ADDRESS,
	FLASH_WRITE_ERROR,
	FLASH_ERASE_ERROR,
	FLASH_ERROR_ADRESSING_MODE //Error setting the device to 4 bit addressing mode.

} FlashStatus_t;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This checks device ID, disables protected areas, and puts the flash device into 4 byte address mode.
//	Returns FLASH_OK on success.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_setup_flash();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This writes data to the flash memory starting at the given address. The write
//  address will wrap around at the page boundary (256 bytes). This function is blocking!
//  If the write is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_write_page(uint32_t addr, uint8_t* data,uint32_t size);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This reads data from the flash memory starting at the given address.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_read(uint32_t addr, uint8_t* data,uint32_t size);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the whole memory. This function is blocking!
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_device();

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the 64k sector containing the given address.This function is blocking!
//   If the erase is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_64k(uint32_t addr);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the 32k sector containing the given address.This function is blocking!
//  If the erase is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_32k(uint32_t addr);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the 4k sector containing the given address.This function is blocking!
//  If the erase is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_4k(uint32_t addr);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This checks if there is a write status register, program or erase operation in
//  progress. Returns FLASH_BUSY or FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_is_busy();


#endif
