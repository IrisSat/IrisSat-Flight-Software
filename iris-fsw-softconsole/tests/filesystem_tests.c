//-------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//	Github: https://github.com/joehowarth17/IrisSat-Flight-Software
//
// File Description:
//  This file contains tests related to the file system. Additional tests
//  are in the littleFS folder in the Libraries folder.
//
// History
// 2020-04-21 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------

#include <FreeRTOS/FreeRTOS-Source/include/FreeRTOS.h>
#include <FreeRTOS/FreeRTOS-Source/include/task.h>
#include "tests.h"

#include "drivers/filesystem_driver.h"

void vTestFS(void * pvParams){
	lfs_file_t file = {0}; //Set to 0 because debugger tries to read fields of struct one of which is a pointer, but since this is on free rtos heap, initial value is a5a5a5a5.

	FilesystemError_t stat = fs_init();
	if(stat != FS_OK){
		while(1){}
	}
	//Mount the file system.
	int err = fs_mount();

    // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    if (err) {
        fs_format();
        fs_mount();
    }

    int result = 1;

	while(1){

	    uint32_t boot_count = 0;
	    result = fs_file_open( &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
	    if(result < 0) while(1){}

	    result = fs_file_read( &file, &boot_count, sizeof(boot_count));
	    if(result < 0) while(1){}

	    // update boot count
	    boot_count += 1;
	    result = fs_file_rewind( &file);
	    if(result < 0) while(1){}

	    result = fs_file_write( &file, &boot_count, sizeof(boot_count));
	    if(result < 0) while(1){}

	    // remember the storage is not updated until the file is closed successfully
	    result = fs_file_close( &file);
	    if(result < 0) while(1){}

	    // release any resources we were using
	    result = fs_unmount();
	    if(result < 0) while(1){}

	    vTaskSuspend(NULL);
	}
}
