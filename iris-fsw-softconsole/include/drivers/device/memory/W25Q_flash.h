#ifndef W25Q_H_
#define W25Q_H_
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  Program flash memory chip on the IrisSat CDH board.
//
// History
// 2021-03-04 by Joseph Howarth
// - Created.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <stdint.h>
#include "drivers/device/memory/flash_common.h"

#define W25Q_PAGE_SIZE             (256)
#define W25Q_SUBSECTOR_SMALL_SIZE  (4096)
#define W25Q_SUBSECTOR_LARGE_SIZE  (32768)
#define W25Q_SECTOR_SIZE           (65536)
#define W25Q_DIE_SIZE              (0x200000)

#define W25Q_ID_BYTE1				(0xEF)
#define W25Q_ID_BYTE2				(0x40)
#define W25Q_ID_BYTE3				(0x15)

typedef enum  {

  W25Q_OP_READ_ID = 0x9F,

  W25Q_OP_READ_STAT_REG_1 = 0x05,
  W25Q_OP_READ_STAT_REG_2 = 0x35,
  W25Q_OP_READ_STAT_REG_3 = 0x15,

  W25Q_OP_WRITE_STAT_REG = 0x01,

  W25Q_OP_WRITE_ENABLE = 0x06,
  W25Q_OP_WRITE_DISABLE = 0x04,

  W25Q_OP_GLOBAL_UNLOCK = 0x98,

  W25Q_OP_READ = 0x0B,
  W25Q_OP_PROGRAM  = 0x02,
  W25Q_OP_ERASE_DIE = 0x60,
  W25Q_OP_ERASE_SECTOR_64k = 0xD8,
  W25Q_OP_ERASE_SECTOR_32k = 0x52,
  W25Q_OP_ERASE_SECTOR_4k = 0x20,

} W25QOperation_t;


typedef struct{

    //Required function pointers.
    void (*spi_write)(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *wr_buffer,uint16_t wr_size);
    void (*spi_read)(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *rd_buffer,uint16_t rd_size);

}
W25Q_Device_t;


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This sets up the hold/wp pins and checks device ID.
//	Returns FLASH_OK on success.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t W25Q_setup_flash(W25Q_Device_t * dev);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This writes data to the flash memory starting at the given address. The write
//  address will wrap around at the page boundary (256 bytes). This function is blocking!
//  If the write is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t W25Q_flash_write_page(W25Q_Device_t * dev,uint32_t addr, uint8_t* data,uint32_t size);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This reads data from the flash memory starting at the given address.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t W25Q_flash_read(W25Q_Device_t * dev,uint32_t addr, uint8_t* data,uint32_t size);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the whole memory. This function is blocking!
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t W25Q_flash_erase_device(W25Q_Device_t * dev);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the 4k sector containing the given address.This function is blocking!
//  If the erase is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t W25Q_flash_erase_4k(W25Q_Device_t * dev,uint32_t addr);



#endif
