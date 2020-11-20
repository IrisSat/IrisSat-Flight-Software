//-------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//	Github: https://github.com/joehowarth17/IrisSat-Flight-Software
//
// File Description:
//  This file contains tests related to the external memory (mram/flash).
//
// History
// 2020-04-21 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------

#include "tests.h"

#include "FreeRTOS.h"
#include "task.h"

#include "mram.h"

#include "flash_common.h"
#include "string.h"

void vTestMRAM(void *pvParameters)
{
    // Test code that writes to all locations of the MRAM, and then reads it back.
    static uint8_t write_buffer[0x10];
    static uint8_t read_buffer1[sizeof(write_buffer)];
    uint8_t status_reg;

    static volatile int error_occurred = 0;

    for (int ix = 0; ix < sizeof(write_buffer); ix++)
    {
        write_buffer[ix] = 0x55;
    }
    for(;;)
    {
        // Loop through all addresses.
        for (int ix = 0; ix < MAX_MRAM_ADDRESS; ix += sizeof(write_buffer))
        {
           for (int ix = 0; ix < sizeof(write_buffer); ix++)
           {
              read_buffer1[ix] = 0xFF;
           }

           vTaskSuspendAll();
           mr2xh40_write(&mram_instances[MRAM_INSTANCE_0], ix, write_buffer, sizeof(write_buffer));
           xTaskResumeAll();

           taskYIELD();

           vTaskSuspendAll();
           mr2xh40_read(&mram_instances[MRAM_INSTANCE_0], ix, read_buffer1, sizeof(read_buffer1));
           xTaskResumeAll();

           for (int iy = 0; iy < sizeof(write_buffer); iy++)
           {
               if (read_buffer1[iy] != write_buffer[iy])
               {
                   error_occurred = 1; // Breakpoint here!
               }
           }

           vTaskDelay(pdMS_TO_TICKS(2000)); // Breakpoint here to make sure you are done!
        }
    }
}

void vTestFlash(void *pvParameters)
{

	FlashDev_t * device = (FlashDev_t *) pvParameters;

	FlashStatus_t result = flash_device_init(device);

	if(result != FLASH_OK){
		while(1);
	}


	while(1){

	uint8_t data_tx[device->page_size];
	uint8_t data_rx[device->page_size];
	uint8_t data_rx2[device->page_size];
	memset(data_tx,0,device->page_size);
	memset(data_rx,0,device->page_size);
	memset(data_rx2,0,2*device->page_size);

	            //A list of addresses used in this test.
	            uint32_t addr[6] = {0,//First page.
	                                5*device->page_size, //5th page
									6*device->page_size,
									device->erase_size,
									device->device_size - device->page_size,
									device->device_size -2*(device->page_size)
	                                };

	            //Prepare some data to write to each page.
	            for(int i=0;i<device->page_size;i++){
	                data_tx[i] = i;
	            }

	            //Start by erasing the device.
	            FlashStatus_t res = flash_erase_device(device);
	            if(res != FLASH_OK){
	                while(1){}
	            }

	            //Verify that the erase device works properly.
	            //All addresses should have 0xFF as the data.
	            for(int j=0; j<6;j++){

	                flash_read(device,addr[j], data_rx, device->page_size);

	                for(int i=0;i<device->page_size;i++){
	                    if(data_rx[i] != 0xFF) while(1){}
	                }
	                memset(data_rx,0,256);
	            }

	            //Now verify that writing is working:
	            //Write to all the addresses on page of data.

	            for(int j=0; j<6;j++){
	                //write
	                res =flash_write(device,addr[j], data_tx, device->page_size);
	                if(res != FLASH_OK) while(1){}

	                //Read
	                flash_read(device,addr[j], data_rx, device->page_size);

	                //Verify
	                for(int i=0;i<device->page_size;i++){

						if(data_rx[i] != data_tx[i]) while(1){}
	                }

	                memset(data_rx,0,256);
	            }

	            //Make sure we can read more than one page at a time:
	            flash_read(device,addr[1], data_rx2, device->page_size*2);
	            for(int i=0;i<device->page_size*2;i++){

	                if(data_rx2[i] != data_tx[i%device->page_size])
	                    while(1){}
	                }

	            //Test the one of the erase functions

	            res = flash_erase(device,addr[0]);
	            if(res != FLASH_OK) while(1){}

	            //Now check that the only the first address is 0.
	            for(int j=0;j<6;j++){

	                flash_read(device,addr[j], data_rx, device->page_size);

	                for(int i=0;i<device->page_size;i++){
	                    if(j <3){
	                    	if(data_rx[i] != 0xFF) while(1){}
	                    }
	                    else{
	                        if(data_tx[i] != data_rx[i]) while(1){}
	                    }
	                }
	                memset(data_rx,0,256);
	            }


	            vTaskSuspend(NULL);
	}
}
