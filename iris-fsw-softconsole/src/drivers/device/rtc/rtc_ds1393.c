//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  Driver for the DS1393 RTC (i.e. the external RTC).
//
// History
// 2019-04-17 by Tamkin Rahman
// - Created.
// 2019-06-23 by Tamkin Rahman
// - Move pin and SPI core definitions to board_definitions.h.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "drivers/device/rtc/rtc_ds1393.h"

#include "board_definitions.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define WRITE_MASK       0x80  // This bit should be set to write to an address. Should not be set to read from an address.

// The data from the RTC is in BCD format.
#define bcd2bin(val) ((val) & 0x0F) + ((val) / 0x10 * 10)
#define bin2bcd(val) (((val) % 10) + ((val) / 10 * 0x10))

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ds1393_init()
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ds1393_read_time(Calendar_t * read_buffer)
{
	uint8_t buffer[7] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	// Note that the calendar time can be read in one transaction because the address
	// increments if the CLK continues to run (and the SS remains enabled).

	uint8_t address = DS1393_REG_SECONDS;

	spi_transaction_block_read_without_toggle(
			RTC_SPI_CORE,
			RTC_SLAVE_CORE,
			&address,
			1,
			buffer,
			sizeof(buffer));

	read_buffer->second = bcd2bin(buffer[0]);
	read_buffer->minute = bcd2bin(buffer[1]);
	read_buffer->hour = bcd2bin(buffer[2]);
	read_buffer->weekday = bcd2bin(buffer[3]);
	read_buffer->day = bcd2bin(buffer[4]);
	read_buffer->month = bcd2bin(buffer[5]);
	read_buffer->year = bcd2bin(buffer[6]);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ds1393_write_time(Calendar_t * write_buffer)
{
	DS1393RegAddresses_t address = DS1393_REG_SECONDS | WRITE_MASK;
	uint8_t buffer[7];
	buffer[0] = bin2bcd(write_buffer->second);
	buffer[1] = bin2bcd(write_buffer->minute);
	buffer[2] = bin2bcd(write_buffer->hour); // Note that bit 6 (0-indexed) is 0, which indicates 0-23 hr format.
	buffer[3] = bin2bcd(write_buffer->weekday);
	buffer[4] = bin2bcd(write_buffer->day);
	buffer[5] = bin2bcd(write_buffer->month);
	buffer[6] = bin2bcd(write_buffer->year);

	spi_transaction_block_write_without_toggle(
			RTC_SPI_CORE,
			RTC_SLAVE_CORE,
			&address,
			1,
			buffer,
			sizeof(buffer));
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ds1393_read_reg(DS1393RegAddresses_t address, uint8_t * buffer)
{
	spi_transaction_block_read_without_toggle(
			RTC_SPI_CORE,
			RTC_SLAVE_CORE,
			&address,
			1,
			buffer,
			1);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void ds1393_write_reg(DS1393RegAddresses_t address, uint8_t value)
{
	DS1393RegAddresses_t write_address = address | WRITE_MASK;
	spi_transaction_block_write_without_toggle(
			RTC_SPI_CORE,
			RTC_SLAVE_CORE,
			&address,
			1,
			&value,
			1);
}
