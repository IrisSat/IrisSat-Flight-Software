#ifndef BOARD_DEFINITIONS_H
#define BOARD_DEFINITIONS_H
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// License:
// 	Available under the GNU General Public License v3.0 (GPL-3.0-or-later)
//
// Repository:
//  Github: https://github.com/UMSATS/cdh-tsat5
//
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
#include "spi.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

// SPI Master and Slave core definitions
#define RTC_SPI_CORE   CORE_SPI_0
#define RTC_SLAVE_CORE SPI_SLAVE_0  // RTC uses MSS_GPIO for SS, so this is not relevant.

#define MRAM0_SPI_CORE   CORE_SPI_0
#define MRAM0_SLAVE_CORE SPI_SLAVE_1 // MRAM0 uses MSS_GPIO for SS, so this is not relevant.

#define FLASH_SPI_CORE   CORE_SPI_0
#define FLASH_SLAVE_CORE SPI_SLAVE_2 // FLASH uses MSS_GPIO for SS, so this is not relevant.

// MSS GPIO definitions
#define LED0          MSS_GPIO_0
#define LED1          MSS_GPIO_1
#define LED2          MSS_GPIO_2 // Note: Not enabled.
#define LED3          MSS_GPIO_3
#define LED4          MSS_GPIO_4 // Note: Not enabled.
#define LED5          MSS_GPIO_5
#define LED6          MSS_GPIO_6
#define LED7          MSS_GPIO_7

#define RTC_SS_PIN     MSS_GPIO_8
#define ADC_SS_PIN     MSS_GPIO_9
#define FLASH_SS_PIN   MSS_GPIO_10
#define RADIO_SS_PIN   MSS_GPIO_11
#define MRAM0_SS_PIN   MSS_GPIO_12


#endif // BOARD_DEFINITIONS_H
