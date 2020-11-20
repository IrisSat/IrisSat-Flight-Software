//------------------------------------------------------------------------------
//
// Repository:
//	Github: https://github.com/joehowarth17/IrisSat-Flight-Software
//
// File Description:
//  Driver for updating the software/FPGA fabric (ISP).
//
// History
// 2020-05-05 by Joseph Howarth
// - Created.
//------------------------------------------------------------------------------

#include "software_update_driver.h"
#include "flash_common.h"
#include "mss_uart.h"
#include "uart.h"
#include "mss_sys_services.h"
#include "string.h"
#include "stdio.h"
#include "mss_spi.h"

static uint32_t programSize = 0;
static uint8_t initialized = 0;

void authenticate_firmware(uint8_t version){
	uint32_t addr = (version)?FIRMWARE_GOLDEN_ADDRESS:FIRMWARE_UPDATE_ADDRESS;
	uint8_t stat = 255;
	if(!initialized){
		MSS_SYS_init(MSS_SYS_NO_EVENT_HANDLER);
		initialized = 1;
	}
	uint8_t dv = 255;
	stat = MSS_SYS_get_design_version(&dv);

	char msg[20];
	sprintf(msg,"design ver. %d\n",dv);
	prvUARTSend(&g_mss_uart0, msg, strlen(msg));

	MSS_SPI_set_slave_select(&g_mss_spi0,MSS_SPI_SLAVE_0);
	uint8_t result = MSS_SYS_initiate_iap(MSS_SYS_PROG_AUTHENTICATE,addr);
	MSS_SPI_clear_slave_select(&g_mss_spi0,MSS_SPI_SLAVE_0);

	if(result == MSS_SYS_SUCCESS){

		prvUARTSend(&g_mss_uart0, "authenticated!\n", strlen("authenticated!\n"));
	}else{
		char resString[30];
		sprintf(resString,"Failed: %d\n",result);
		prvUARTSend(&g_mss_uart0, resString, strlen(resString));
	}

}

void initiate_firmware_update(uint8_t version){
	uint32_t addr = (version)?FIRMWARE_GOLDEN_ADDRESS:FIRMWARE_UPDATE_ADDRESS;
	if(!initialized){
		MSS_SYS_init(MSS_SYS_NO_EVENT_HANDLER);
		initialized = 1;
	}

	prvUARTSend(&g_mss_uart0, "Starting IAP...\n", strlen("Starting IAP...\n"));

	MSS_SPI_set_slave_select(&g_mss_spi0,MSS_SPI_SLAVE_0);
	uint8_t result = MSS_SYS_initiate_iap(MSS_SYS_PROG_PROGRAM,addr);
	MSS_SPI_clear_slave_select(&g_mss_spi0,MSS_SPI_SLAVE_0);

	//If we get here the IAP failed...
	char resString[30];
	sprintf(resString,"Failed: %d\n",result);
	prvUARTSend(&g_mss_uart0, resString, strlen(resString));

}

void repeat_program(uint32_t version){

	uint32_t numTransmits = programSize/512;
	uint32_t remaining = programSize%512;
	uint8_t buff[512];

	uint32_t index = (version)?FIRMWARE_GOLDEN_ADDRESS:FIRMWARE_UPDATE_ADDRESS;
	for(int i=0;i<numTransmits;i++){

		flash_read(flash_devices[PROGRAM_FLASH], index, buff, 512);
		prvUARTSend(&g_mss_uart0, buff, 512);
		index += 512;
	}

	flash_read(flash_devices[PROGRAM_FLASH], index, buff, remaining);
	prvUARTSend(&g_mss_uart0, buff, remaining);

}
void set_program_size(uint32_t size, uint8_t version){
	programSize = size;
	flash_device_init(flash_devices[PROGRAM_FLASH]);

	if(version == 0){
		uint32_t start = FIRMWARE_UPDATE_ADDRESS-1;
		while(start < flash_devices[PROGRAM_FLASH]->device_size){
			flash_erase(flash_devices[PROGRAM_FLASH], start);
			start += flash_devices[PROGRAM_FLASH]->erase_size;
		}
	}
	else{
		uint32_t start = FIRMWARE_GOLDEN_ADDRESS-1;
		while(start < FIRMWARE_UPDATE_ADDRESS){
			flash_erase(flash_devices[PROGRAM_FLASH], start);
			start += flash_devices[PROGRAM_FLASH]->erase_size;
		}

	}

	uint8_t spi_dir[13] = {0x00, 0x01,0x00,0x00,0x02,0x00,0x00,0x00,0x10,0x00,0x03,0x00,0x0a};
	FlashStatus_t stat= flash_write(flash_devices[PROGRAM_FLASH], 0, spi_dir, sizeof(spi_dir));

}
void save_program(void * buff, uint16_t size, uint8_t version){

	static uint32_t pos_golden = FIRMWARE_UPDATE_ADDRESS;
	static uint32_t pos_update = FIRMWARE_GOLDEN_ADDRESS;


	if(version == 0){
		FlashStatus_t stat= flash_write(flash_devices[PROGRAM_FLASH], pos_golden, buff, size);
		if(stat == FLASH_OK) pos_golden += size;
	}
	else if(version == 1){
		FlashStatus_t stat= flash_write(flash_devices[PROGRAM_FLASH], pos_update, buff, size);
		if(stat == FLASH_OK) pos_update += size;
	}
}

