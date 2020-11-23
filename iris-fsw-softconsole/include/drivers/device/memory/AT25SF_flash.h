#ifndef AT25SF_H_
#define AT25SF_H_
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//	Github: https://github.com/joehowarth17/IrisSat-Flight-Software
//
// File Description:
//  Dev Kit on-board flash memory (AT25SF161) functions and definitions.
//
// History
// 2020-05-04 by Joseph Howarth
// - Created.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <stdint.h>
#include "flash_common.h"

#define AT25SF_PAGE_SIZE             (256)
#define AT25SF_SUBSECTOR_SMALL_SIZE  (4096)
#define AT25SF_SUBSECTOR_LARGE_SIZE  (32768)
#define AT25SF_SECTOR_SIZE           (65536)
#define AT25SF_DIE_SIZE              (0x200000)

#define AT25SF_ID_BYTE1				(0x1F)
#define AT25SF_ID_BYTE2				(0x86)
#define AT25SF_ID_BYTE3				(0x01)

typedef enum  {

  AT25SF_OP_READ_ID = 0x9F,

  AT25SF_OP_READ_STAT_REG_1 = 0x05,
  AT25SF_OP_READ_STAT_REG_2 = 0x35,
  AT25SF_OP_WRITE_STAT_REG = 0x01,

  AT25SF_OP_WRITE_ENABLE = 0x06,
  AT25SF_OP_WRITE_DISABLE = 0x04,

  AT25SF_OP_READ = 0x0B,
  AT25SF_OP_PROGRAM  = 0x02,
  AT25SF_OP_ERASE_DIE = 0x60,
  AT25SF_OP_ERASE_SECTOR_64k = 0xD8,
  AT25SF_OP_ERASE_SECTOR_32k = 0x52,
  AT25SF_OP_ERASE_SECTOR_4k = 0x20,

} AT25SFOperation_t;


typedef struct{

    //Required function pointers.
    void (*spi_write)(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *wr_buffer,uint16_t wr_size);
    void (*spi_read)(uint8_t *cmd_buffer,uint16_t cmd_size,uint8_t *rd_buffer,uint16_t rd_size);

}
AT25SF_Device_t;


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This sets up the hold/wp pins and checks device ID.
//	Returns FLASH_OK on success.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t AT25SF_setup_flash(AT25SF_Device_t * dev);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This writes data to the flash memory starting at the given address. The write
//  address will wrap around at the page boundary (256 bytes). This function is blocking!
//  If the write is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t AT25SF_flash_write_page(AT25SF_Device_t * dev,uint32_t addr, uint8_t* data,uint32_t size);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This reads data from the flash memory starting at the given address.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t AT25SF_flash_read(AT25SF_Device_t * dev,uint32_t addr, uint8_t* data,uint32_t size);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the whole memory. This function is blocking!
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t AT25SF_flash_erase_device(AT25SF_Device_t * dev);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This erases the 4k sector containing the given address.This function is blocking!
//  If the erase is successful, the function will return FLASH_OK.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t AT25SF_flash_erase_4k(AT25SF_Device_t * dev,uint32_t addr);



#endif
