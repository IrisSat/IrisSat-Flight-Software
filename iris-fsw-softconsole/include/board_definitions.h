#ifndef BOARD_DEFINITIONS_H
#define BOARD_DEFINITIONS_H
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  Contains definitions for pins and SPI cores for the CDH software.
//
// History
// 2019-06-23 by Tamkin Rahman
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "drivers/protocol/spi.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------



// SPI Master and Slave core definitions
#define RTC_SPI_CORE   CORE_SPI_0
#define RTC_SLAVE_CORE SPI_SLAVE_0

#define MRAM0_SPI_CORE   CORE_SPI_2
#define MRAM0_SLAVE_CORE SPI_SLAVE_0 // MRAM0 uses MSS_GPIO for SS, so this is not relevant.

#define FLASH_SPI_CORE   CORE_SPI_3
#define FLASH_SLAVE_CORE SPI_SLAVE_0 // FLASH uses MSS_GPIO for SS, so this is not relevant.

#define ADCS_SPI_CORE   CORE_SPI_1
#define ADCS_SLAVE_CORE SPI_SLAVE_0 // ADS uses MSS_GPIO for SS, so this is not relevant.
#define MRAM1_SPI_CORE   CORE_SPI_4
#define MRAM1_SLAVE_CORE SPI_SLAVE_0 // MRAM1 uses MSS_GPIO for SS, so this is not relevant.

// MRAM_n in SoftConsole is equivalent to MRAM_(n+1) in schematics

// MSS GPIO definitions
#define LED0          MSS_GPIO_0
#define LED1          MSS_GPIO_1
#define LED2          MSS_GPIO_2 // Note: Not enabled.
#define LED3          MSS_GPIO_3
#define LED4          MSS_GPIO_4 // Note: Not enabled.
#define LED5          MSS_GPIO_5
#define LED6          MSS_GPIO_6
#define LED7          MSS_GPIO_7


#endif // BOARD_DEFINITIONS_H
