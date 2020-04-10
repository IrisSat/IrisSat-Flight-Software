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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


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

static lfs_t lfs;
static const struct lfs_config config = {	.read  = fs_read,
											.prog  = fs_prog,
											.erase = fs_erase,
											.sync  = fs_sync,

											// block device configuration
											.read_size = 1,
											.prog_size = 256,
											.block_size = 4096,		//Erase size.
											.block_count = 32768,
											.cache_size = 256, 		//Must be a multiple of the read and program sizes, and a factor of the block size
											.lookahead_size = 2048, //The lookahead buffer is stored as a compact bitmap, so each byte of RAM can track 8 blocks. Must be a multiple of 8.
											.block_cycles = 500};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


 FilesystemError_t fs_init(){}

 int fs_format(){
	 return lfs_format(&lfs, &config);
 }

 int fs_mount(){
	 return lfs_mount(&lfs, &config);
 }

 int fs_unmount(){
	 return lfs_unmount(&lfs);
 }

 int fs_remove( const char *path){
	 return lfs_remove(&lfs, path);
 }

 int fs_rename( const char *oldpath, const char *newpath){
	 return lfs_rename(&lfs, oldpath, newpath);
 }

 int fs_stat( const char *path, struct lfs_info *info){
	 return lfs_stat(&lfs, path, info);
 }

 lfs_ssize_t fs_getattr( const char *path, uint8_t type, void *buffer, lfs_size_t size){
	 return lfs_getattr(&lfs, path, type, buffer, size);
 }

 int fs_setattr( const char *path, uint8_t type, const void *buffer, lfs_size_t size){
	 return lfs_setattr(&lfs, path, type, buffer, size);
 }

 int fs_removeattr( const char *path, uint8_t type){
	 return lfs_removeattr(&lfs, path, type);
 }

 int fs_file_open( lfs_file_t *file, const char *path, int flags){
	 return lfs_file_open(&lfs, file, path, flags);
 }

 int fs_file_opencfg( lfs_file_t *file, const char *path, int flags, const struct lfs_file_config *config){
	 return lfs_file_opencfg(&lfs, file, path, flags, config);
 }

 int fs_file_close( lfs_file_t *file){
	 return lfs_file_close(&lfs, file);
 }

 int fs_file_sync( lfs_file_t *file){
	 return lfs_file_sync(&lfs, file);
 }

 lfs_ssize_t fs_file_read( lfs_file_t *file, void *buffer, lfs_size_t size){
	 return lfs_file_read(&lfs, file, buffer, size);
 }

 lfs_ssize_t fs_file_write( lfs_file_t *file, const void *buffer, lfs_size_t size){
	 return lfs_file_write(&lfs, file, buffer, size);
 }

 lfs_soff_t fs_file_seek( lfs_file_t *file, lfs_soff_t off, int whence){
	 return lfs_file_seek(&lfs, file, off, whence);
 }

 int fs_file_truncate( lfs_file_t *file, lfs_off_t size){
	 return lfs_file_truncate(&lfs, file, size);
 }

 lfs_soff_t fs_file_tell( lfs_file_t *file){
	 return lfs_file_tell(&lfs, file);
 }

 int fs_file_rewind( lfs_file_t *file){
	 return lfs_file_rewind(&lfs, file);
 }

 lfs_soff_t fs_file_size( lfs_file_t *file){
	 return lfs_file_size(&lfs, file);
 }

 int fs_mkdir( const char *path){
	 return lfs_mkdir(&lfs, path);
 }

 int fs_dir_open( lfs_dir_t *dir, const char *path){
	 return lfs_dir_open(&lfs, dir, path);
 }

 int fs_dir_close( lfs_dir_t *dir){
	 return lfs_dir_close(&lfs, dir);
 }

 int fs_dir_read( lfs_dir_t *dir, struct lfs_info *info){
	 return lfs_dir_read(&lfs, dir, info);
 }

 int fs_dir_seek( lfs_dir_t *dir, lfs_off_t off){
	 return lfs_dir_seek(&lfs, dir, off);
 }

 lfs_soff_t fs_dir_tell( lfs_dir_t *dir){
	 return lfs_dir_tell(&lfs, dir);
 }

 int fs_dir_rewind( lfs_dir_t *dir){
	 return lfs_dir_rewind(&lfs, dir);
 }

 lfs_ssize_t fs_size(){
	 return lfs_fs_size(&lfs);
 }

 int fs_traverse( int (*cb)(void*, lfs_block_t), void *data){
	 return lfs_fs_traverse(&lfs, cb, data);
 }



 int fs_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size){}

 int fs_prog(const struct lfs_config *c, lfs_block_t block,lfs_off_t off, const void *buffer, lfs_size_t size){}

 int fs_erase(const struct lfs_config *c, lfs_block_t block){}

  int fs_sync(const struct lfs_config *c){}
