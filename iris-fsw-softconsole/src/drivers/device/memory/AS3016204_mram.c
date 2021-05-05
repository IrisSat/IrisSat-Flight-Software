//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  Source file for the AS3016204 mram.
//
// History
// 2021-03-25 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "drivers/device/memory/AS3016204_mram.h"
#include "board_definitions.h"

typedef enum{

    AS_MRAM_CMD_WREN = 0x06, //Write enable
    AS_MRAM_CMD_WRDI = 0x04, //Write disable
    AS_MRAM_CMD_RDSR = 0x05, //Read status reg
    AS_MRAM_CMD_WRSR = 0x01, //Write status reg
    AS_MRAM_CMD_RDID = 0x9F, //Read device ID
    AS_MRAM_CMD_READ = 0x03, //Read memory
    AS_MRAM_CMD_WRTE = 0x02, //Write memory
    AS_MRAM_CMD_DPDE = 0xB9, //Enter deep sleep
    AS_MRAM_CMD_DPDX = 0xAB, //Exit deep sleep
} AS3016204_cmd_bytes;



void asMram_init(){

    uint8_t id_good = 1;
    uint8_t id[4] = {0};

    uint8_t cmd = AS_MRAM_CMD_RDID;

    spi_transaction_block_read_without_toggle(MRAM1_SPI_CORE, MRAM1_SLAVE_CORE, &cmd,1,id, 4);

    //ID bytes are from data sheet.
    if(id[0] != 0xE6 || id[1] != 0x01 || id[2] != 0x14 || id[3] != 0x01){

        id_good = 0; //Breakpoint here to check id. Would be good to include error codes in this driver.
    }

}

void asMram_read(   uint32_t address,uint8_t * rd_buffer, uint32_t rd_buffer_size){

    //TODO: Add valid mem location checking, error code return.
    uint8_t cmd[4] = { AS_MRAM_CMD_READ,
                      (address >> 16) & 0x07,
                      (address >> 8) & 0xFF,
                      (address) & 0xFF
    };
    spi_transaction_block_read_without_toggle(
                    MRAM1_SPI_CORE,
                    MRAM1_SLAVE_CORE,

                    cmd,
                    sizeof(cmd),
                    rd_buffer,
                    rd_buffer_size);


}

void asMram_write(  uint32_t address, uint8_t * wr_buffer, uint32_t wr_buffer_size){

    //TODO: Add valid mem location checking, error code return.

    //Apparently default mode doesn't require WREN.
    uint8_t cmd[4] = { AS_MRAM_CMD_WRTE,
                      (address >> 16) & 0x07,
                      (address >> 8) & 0xFF,
                      (address) & 0xFF
    };

    spi_transaction_block_write_without_toggle(
                    MRAM1_SPI_CORE,
                    MRAM1_SLAVE_CORE,
                    cmd,
                    sizeof(cmd),
                    wr_buffer,
                    wr_buffer_size);

}
