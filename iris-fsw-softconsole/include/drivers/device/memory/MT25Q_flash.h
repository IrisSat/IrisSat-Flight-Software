#ifndef MT25Q_H
#define MT25Q_H
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  External flash memory (MT25Q) functions and definitions.
//
// History
// 2020-03-07 by Joseph Howarth
// - Created.
// 2020-03-30 by Joseph Howarth 
// - Modified to use flash interface.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdint.h>
#include "flash_common.h"

#define MT25Q_PAGE_SIZE             (256)
#define MT25Q_SUBSECTOR_SMALL_SIZE  (4096)
#define MT25Q_SUBSECTOR_LARGE_SIZE  (32768)
#define MT25Q_SECTOR_SIZE           (65536)
#define MT25Q_DIE_SIZE              (0x4000000)


typedef enum  {

  MT25Q_OP_RST_EN = 0x66,
  MT25Q_OP_RST = 0x99,

  MT25Q_OP_READ_ID = 0xAF,

  MT25Q_OP_READ_STAT_REG = 0x05,
  MT25Q_OP_WRITE_STAT_REG = 0x01,

  MT25Q_OP_READ_FLAG_REG = 0x70,
  MT25Q_OP_CLEAR_FLAG_REG =0x50,

  MT25Q_OP_READ_EXT_REG = 0xC8,	//Read Extended Addressing mode register.
  MT25Q_OP_WRITE_EXT_REG = 0xC5,

  MT25Q_OP_READ_DEFAULT_CONFIG = 0x85,
  MT25Q_OP_WRITE_DEFAULT_CONFIG = 0xB1,

  MT25Q_OP_ENABLE_4_BYTE_MODE = 0xB7,

  MT25Q_OP_WRITE_SECTOR_PROTECTION = 0x2C,
  MT25Q_OP_READ_PASSWORD = 0x27,

  MT25Q_OP_WRITE_ENABLE = 0x06,
  MT25Q_OP_WRITE_DISABLE = 0x04,

  MT25Q_OP_READ = 0x13,	// This is for 4-byte addressing.
  MT25Q_OP_PROGRAM  = 0x12,
  MT25Q_OP_ERASE_DIE = 0xC4,
  MT25Q_OP_ERASE_SECTOR_64k = 0xDC,
  MT25Q_OP_ERASE_SECTOR_32k = 0x5C,
  MT25Q_OP_ERASE_SECTOR_4k = 0x21,

} MT25QOperation_t;

typedef struct{

    //Required function pointers.
    void (*spi_write)(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *wr_buffer,uint16_t wr_size);
    void (*spi_read)(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *rd_buffer,uint16_t rd_size);

    //Device specific info.
    uint8_t num_dies;
    uint32_t size;
}
MT25Q_Device_t;



//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This checks device ID, disables protected areas, and puts the flash device into 4 byte address mode if needed.
//	Returns FLASH_OK on success.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_setup_flash(MT25Q_Device_t * dev);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This writes data to the flash memory starting at the given address. The write
//  address will wrap around at the page boundary (256 bytes). This function is blocking!
//  If the write is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_write_page(MT25Q_Device_t * dev,uint32_t addr, uint8_t* data,uint32_t size);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This reads data from the flash memory starting at the given address.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_read(MT25Q_Device_t * dev,uint32_t addr, uint8_t* data,uint32_t size);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the whole memory. This function is blocking!
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_device(MT25Q_Device_t * dev);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the 64k sector containing the given address.This function is blocking!
//   If the erase is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_64k(MT25Q_Device_t * dev,uint32_t addr);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the 32k sector containing the given address.This function is blocking!
//  If the erase is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_32k(MT25Q_Device_t * dev,uint32_t addr);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the 4k sector containing the given address.This function is blocking!
//  If the erase is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t MT25Q_flash_erase_4k(MT25Q_Device_t * dev,uint32_t addr);

#endif
