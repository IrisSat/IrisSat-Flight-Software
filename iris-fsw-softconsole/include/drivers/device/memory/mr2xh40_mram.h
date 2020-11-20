#ifndef MR2XH40_MRAM_H_
#define MR2XH40_MRAM_H_
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// License:
//  Available under MIT license.
//
// Repository:
//  Github: https://github.com/UMSATS/cdh-tsat5
//
// File Description:
//  Driver for the MR2xH40 MRAM part. Note that this driver expects the Write Protect (/WP) and /Hold pins are pulled high (i.e. inactive).
//
// History
// 2019-04-25 by Tamkin Rahman
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "spi.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// The MRAM used is a 4Mbit part.
#define MAX_MRAM_ADDRESS  0x7FFFF

// Locations that are empty contain 0xFF.
#define ERASE_BYTE        0xFF

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTURES AND STRUCTURE TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
    CoreSPIInstance_t core;
    spi_slave_t slave;
    mss_gpio_id_t cs_pin;
} MRAMInstance_t;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Configures the SPI and GPIO configurations for this MRAM instance. Should be called once, prior to calling other functions.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void mr2xh40_init(
    MRAMInstance_t * mram  // The MRAM instance to initialize.
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Read data from the specified address into a given buffer. If the read address reaches a value greater than the MAX_MRAM_ADDRESS, then it will rollover
//  back to 0.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void mr2xh40_read(
    MRAMInstance_t * mram,  // The MRAM instance to read from.
    uint32_t address,       // The starting address to read from.
    uint8_t * rd_buffer,    // The buffer to place the read data into.
    size_t rd_buffer_size   // The size of the read buffer.
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Write data to the specified address from a given buffer. If the write address reaches a value greater than the MAX_MRAM_ADDRESS, then it will rollover
//  back to 0.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void mr2xh40_write(
    MRAMInstance_t * mram,  // The MRAM instance to write to.
    uint32_t address,       // The starting address to write to.
    uint8_t * wr_buffer,    // The buffer containing the data to write.
    size_t wr_buffer_size   // The size of the write buffer.
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Read the contents of a status register into a single byte buffer.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void mr2xh40_read_status_register(
    MRAMInstance_t * mram,  // The MRAM instance to read from.
    uint8_t * buffer        // The 1-byte buffer to place the data into.
);

#endif /* MR2XH40_MRAM_H_ */
