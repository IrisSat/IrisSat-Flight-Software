//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// MBSat-1
//
// Repository:
//	Github: https://github.com/joehowarth17/ManitobaSat-Flight-Software
//
// File Description:
//  Driver interface for the file system.
//
// History
// 2020-04-10 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "filesystem_driver.h"
#include "flash_common.h"

#include "FreeRTOS.h"
#include "semphr.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#define FS_READ_SIZE		1
#define FS_PROG_SIZE		256
#define FS_BLOCK_SIZE		4096
#define FS_CACHE_SIZE		256
#define FS_LOOKAHEAD_SIZE	2048
#define FS_BLOCK_CYCLES		500

#define FS_MAX_OPEN_FILES	3


#define FS_FLASH_DEVICE	DATA_FLASH
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTURES AND STRUCTURE TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//		Read a region in a block. Negative error codes are propagated to the user.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int fs_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//		Program a region in a block. The block must have previously
//		been erased. Negative error codes are propagated to the user. May return
//		LFS_ERR_CORRUPT if the block should be  considered bad.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int fs_prog(const struct lfs_config *c, lfs_block_t block,lfs_off_t off, const void *buffer, lfs_size_t size);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
// 		Erase a block. A block must be erased before being programmed.
// 		The state of an erased block is undefined. Negative error codes
// 		are propagated to the user.
// 		May return LFS_ERR_CORRUPT if the block should be considered bad.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int fs_erase(const struct lfs_config *c, lfs_block_t block);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
// 		Sync the state of the underlying block device. Negative error codes
// 		are propagated to the user.
//
//		See: https://github.com/ARMmbed/littlefs/issues/408
//		The sync callback marks the point in time where littlefs needs pending
//		write operations to be reflected on disk.
//		Though it's worth noting that polling during prog/erase may be easier to implement. <-- We're gonna do this!
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
 int fs_sync(const struct lfs_config *c);


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// GLOBALS AND FILE_SCOPE VARIABLES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//Buffers
static uint8_t fs_lookahead_buffer[FS_LOOKAHEAD_SIZE];
static uint8_t fs_read_buffer[FS_CACHE_SIZE];
static uint8_t fs_write_buffer[FS_CACHE_SIZE];
static uint8_t file_buffers[FS_MAX_OPEN_FILES][FS_CACHE_SIZE];
static struct lfs_file_config file_configs[FS_MAX_OPEN_FILES];
static uint8_t open_files;

static lfs_t lfs;
static struct lfs_config config = {	.read  = fs_read,
											.prog  = fs_prog,
											.erase = fs_erase,
											.sync  = fs_sync,

											// block device configuration
											.read_size = FS_READ_SIZE,
											.prog_size = FS_PROG_SIZE,
											.block_size = 4096,		//Erase size.

											.cache_size = 256, 		//Must be a multiple of the read and program sizes, and a factor of the block size
											.lookahead_size = 2048, //The lookahead buffer is stored as a compact bitmap, so each byte of RAM can track 8 blocks. Must be a multiple of 8.
											.block_cycles = 500,

											.lookahead_buffer = fs_lookahead_buffer,
											.read_buffer = fs_read_buffer,
											.prog_buffer = fs_write_buffer };

static SemaphoreHandle_t fs_lock_handle;


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


 FilesystemError_t fs_init(){

	 FilesystemError_t result = FS_OK;

	 open_files = 0;
	 //Get the total number of blocks by dividing the device byte count by the block byte count.
	 config.block_count = flash_devices[DATA_FLASH]->device_size/FS_BLOCK_SIZE;

	 //Setup the mutex. See https://github.com/ARMmbed/littlefs/issues/156 and
	 //						https://github.com/ARMmbed/littlefs/pull/317
	 fs_lock_handle = xSemaphoreCreateRecursiveMutex();
	 if(fs_lock_handle == NULL){
		 result =  FS_ERR_LOCK;
	 }

	 return result;
 }

int fs_format(){

    int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		result = lfs_format(&lfs, &config);
		xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_mount(){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		result = lfs_mount(&lfs, &config);
		xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_unmount(){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		result =  lfs_unmount(&lfs);
		xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_remove( const char *path){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		result = lfs_remove(&lfs, path);
		xSemaphoreGiveRecursive(fs_lock_handle);
	}
	 return result;
}

int fs_rename( const char *oldpath, const char *newpath){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		result = lfs_rename(&lfs, oldpath, newpath);
		xSemaphoreGiveRecursive(fs_lock_handle);
	}
	 return result;
}

int fs_stat( const char *path, struct lfs_info *info){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		result = lfs_stat(&lfs, path, info);
		xSemaphoreGiveRecursive(fs_lock_handle);
	}
	 return result;
}

lfs_ssize_t fs_getattr( const char *path, uint8_t type, void *buffer, lfs_size_t size){
	lfs_ssize_t result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		result = lfs_getattr(&lfs, path, type, buffer, size);
		xSemaphoreGiveRecursive(fs_lock_handle);
	}
	 return result;
}

int fs_setattr( const char *path, uint8_t type, const void *buffer, lfs_size_t size){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		result = lfs_setattr(&lfs, path, type, buffer, size);
		xSemaphoreGiveRecursive(fs_lock_handle);
	}
	 return result;
}

int fs_removeattr( const char *path, uint8_t type){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		result = lfs_removeattr(&lfs, path, type);
		xSemaphoreGiveRecursive(fs_lock_handle);
	}
	 return result;
}

int fs_file_open( lfs_file_t *file, const char *path, int flags){

	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){

		if(open_files<FS_MAX_OPEN_FILES){

			file_configs[open_files].attr_count = 0;
			file_configs[open_files].attrs = 0;
			file_configs[open_files].buffer = file_buffers[open_files];

			result = lfs_file_opencfg(&lfs, file, path, flags, &file_configs[open_files]);

			if(result >=0){
				//File open was successful, increment number of open files.
				open_files += 1;
			}
		}
		else{
			result = FS_ERR_OPENFILES;
		}

		xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_file_close( lfs_file_t *file){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){

		result = lfs_file_close(&lfs, file);

		if(result >=0){
			//File close was successful, decrement number of open files.
			open_files -= 1;

			//TODO:Not sure if we should clear the file buffer. Check if lfs does this.
		}

		xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_file_sync( lfs_file_t *file){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_file_sync(&lfs, file);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

lfs_ssize_t fs_file_read( lfs_file_t *file, void *buffer, lfs_size_t size){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_file_read(&lfs, file, buffer, size);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

lfs_ssize_t fs_file_write( lfs_file_t *file, const void *buffer, lfs_size_t size){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_file_write(&lfs, file, buffer, size);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

lfs_soff_t fs_file_seek( lfs_file_t *file, lfs_soff_t off, int whence){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_file_seek(&lfs, file, off, whence);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_file_truncate( lfs_file_t *file, lfs_off_t size){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_file_truncate(&lfs, file, size);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

lfs_soff_t fs_file_tell( lfs_file_t *file){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_file_tell(&lfs, file);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_file_rewind( lfs_file_t *file){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_file_rewind(&lfs, file);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

 lfs_soff_t fs_file_size( lfs_file_t *file){
		lfs_soff_t result = FS_ERR_LOCK;

		if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
			 result =  lfs_file_size(&lfs, file);
			 xSemaphoreGiveRecursive(fs_lock_handle);
		}

		return result;
}

int fs_mkdir( const char *path){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_mkdir(&lfs, path);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_dir_open( lfs_dir_t *dir, const char *path){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_dir_open(&lfs, dir, path);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_dir_close( lfs_dir_t *dir){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_dir_close(&lfs, dir);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_dir_read( lfs_dir_t *dir, struct lfs_info *info){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_dir_read(&lfs, dir, info);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
 }

int fs_dir_seek( lfs_dir_t *dir, lfs_off_t off){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_dir_seek(&lfs, dir, off);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

lfs_soff_t fs_dir_tell( lfs_dir_t *dir){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_dir_tell(&lfs, dir);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_dir_rewind( lfs_dir_t *dir){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_dir_rewind(&lfs, dir);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

lfs_ssize_t fs_size(){
	lfs_ssize_t result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_fs_size(&lfs);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}

int fs_traverse( int (*cb)(void*, lfs_block_t), void *data){
	int result = FS_ERR_LOCK;

	if(xSemaphoreTakeRecursive(fs_lock_handle,portMAX_DELAY) == pdTRUE){
		 result =  lfs_fs_traverse(&lfs, cb, data);
		 xSemaphoreGiveRecursive(fs_lock_handle);
	}

	return result;
}



int fs_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size){

	int result = FS_OK;

	uint32_t addr = (block*FS_BLOCK_SIZE)+off;

	FlashStatus_t stat = flash_read(flash_devices[FS_FLASH_DEVICE], addr, buffer, size);

	//TODO: Pass through flash error value.
	if(stat != FLASH_OK){
		result = FS_ERR_IO;
	}

	return result;

}

int fs_prog(const struct lfs_config *c, lfs_block_t block,lfs_off_t off, const void *buffer, lfs_size_t size){

	int result = FS_OK;

	uint32_t addr = (block*FS_BLOCK_SIZE)+off;

	FlashStatus_t stat = flash_write(flash_devices[FS_FLASH_DEVICE], addr, buffer, size);

	//TODO: Pass through flash error value.
	if(stat != FLASH_OK){
		result = FS_ERR_IO;
	}

	return result;
}

int fs_erase(const struct lfs_config *c, lfs_block_t block){

	int result = FS_OK;

	uint32_t addr = (block*FS_BLOCK_SIZE);

	FlashStatus_t stat = flash_erase(flash_devices[FS_FLASH_DEVICE], addr);

	//TODO: Pass through flash error value.
	if(stat != FLASH_OK){
		result = FS_ERR_IO;
	}

	return result;

}

int fs_sync(const struct lfs_config *c){
	//Since our flash read/write/erase functions are blocking,
	//then there should be no need to sync, since any operations will be reflected
	// on the flash devices as soon as the write/erase functions return.
	return FS_OK;
}
