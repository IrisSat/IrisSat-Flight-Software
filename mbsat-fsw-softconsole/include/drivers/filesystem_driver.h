#ifndef FS_DRIVER_H
#define FS_DRIVER_H
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
//
//
//	These functions wrap the littlefs user facing API, making it
// 	thread-safe with freertos.
//
//	This driver also handles the buffers needed by littlefs and hooks
//  up the file system to the flash driver.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "lfs.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTURES AND STRUCTURE TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef enum{

	FS_OK			= 0,
    FS_ERR_IO          ,  // Error during device operation
    FS_ERR_CORRUPT     ,  // Corrupted
    FS_ERR_NOENT       ,   // No directory entry
    FS_ERR_EXIST       ,  // Entry already exists
    FS_ERR_NOTDIR      ,  // Entry is not a dir
    FS_ERR_ISDIR       ,  // Entry is a dir
    FS_ERR_NOTEMPTY    ,  // Dir is not empty
    FS_ERR_BADF        ,   // Bad file number
    FS_ERR_FBIG        ,  // File too large
    FS_ERR_INVAL       ,  // Invalid parameter
    FS_ERR_NOSPC       ,  // No space left on device
    FS_ERR_NOMEM       ,  // No more memory available
    FS_ERR_NOATTR      ,  // No data/attr available
    FS_ERR_NAMETOOLONG ,  // File name too long
	FS_ERR_LOCK		   ,  // Error creating mutex.
	FS_ERR_OPENFILES   ,  //Too many open files.
} FilesystemError_t;


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

FilesystemError_t fs_init();

/// Filesystem functions ///

// Format a block device with the littlefs
//
// Requires a littlefs object and config struct. This clobbers the littlefs
// object, and does not leave the filesystem mounted. The config struct must
// be zeroed for defaults and backwards compatibility.
//
// Returns a negative error code on failure.
int fs_format();

// Mounts a littlefs
//
// Requires a littlefs object and config struct. Multiple filesystems
// may be mounted simultaneously with multiple littlefs objects. Both
// lfs and config must be allocated while mounted. The config struct must
// be zeroed for defaults and backwards compatibility.
//
// Returns a negative error code on failure.
int fs_mount();

// Unmounts a littlefs
//
// Does nothing besides releasing any allocated resources.
// Returns a negative error code on failure.
int fs_unmount();

/// General operations ///

// Removes a file or directory
//
// If removing a directory, the directory must be empty.
// Returns a negative error code on failure.
int fs_remove( const char *path);

// Rename or move a file or directory
//
// If the destination exists, it must match the source in type.
// If the destination is a directory, the directory must be empty.
//
// Returns a negative error code on failure.
int fs_rename( const char *oldpath, const char *newpath);

// Find info about a file or directory
//
// Fills out the info structure, based on the specified file or directory.
// Returns a negative error code on failure.
int fs_stat( const char *path, struct lfs_info *info);

// Get a custom attribute
//
// Custom attributes are uniquely identified by an 8-bit type and limited
// to LFS_ATTR_MAX bytes. When read, if the stored attribute is smaller than
// the buffer, it will be padded with zeros. If the stored attribute is larger,
// then it will be silently truncated. If no attribute is found, the error
// LFS_ERR_NOATTR is returned and the buffer is filled with zeros.
//
// Returns the size of the attribute, or a negative error code on failure.
// Note, the returned size is the size of the attribute on disk, irrespective
// of the size of the buffer. This can be used to dynamically allocate a buffer
// or check for existance.
lfs_ssize_t fs_getattr( const char *path, uint8_t type, void *buffer, lfs_size_t size);

// Set custom attributes
//
// Custom attributes are uniquely identified by an 8-bit type and limited
// to LFS_ATTR_MAX bytes. If an attribute is not found, it will be
// implicitly created.
//
// Returns a negative error code on failure.
int fs_setattr( const char *path, uint8_t type, const void *buffer, lfs_size_t size);

// Removes a custom attribute
//
// If an attribute is not found, nothing happens.
//
// Returns a negative error code on failure.
int fs_removeattr( const char *path, uint8_t type);


/// File operations ///

// Open a file
//
// The mode that the file is opened in is determined by the flags, which
// are values from the enum lfs_open_flags that are bitwise-ored together.
//
// Returns a negative error code on failure.
int fs_file_open( lfs_file_t *file, const char *path, int flags);

// Close a file
//
// Any pending writes are written out to storage as though
// sync had been called and releases any allocated resources.
//
// Returns a negative error code on failure.
int fs_file_close( lfs_file_t *file);

// Synchronize a file on storage
//
// Any pending writes are written out to storage.
// Returns a negative error code on failure.
int fs_file_sync( lfs_file_t *file);

// Read data from file
//
// Takes a buffer and size indicating where to store the read data.
// Returns the number of bytes read, or a negative error code on failure.
lfs_ssize_t fs_file_read( lfs_file_t *file, void *buffer, lfs_size_t size);

// Write data to file
//
// Takes a buffer and size indicating the data to write. The file will not
// actually be updated on the storage until either sync or close is called.
//
// Returns the number of bytes written, or a negative error code on failure.
lfs_ssize_t fs_file_write( lfs_file_t *file, const void *buffer, lfs_size_t size);

// Change the position of the file
//
// The change in position is determined by the offset and whence flag.
// Returns the new position of the file, or a negative error code on failure.
lfs_soff_t fs_file_seek( lfs_file_t *file, lfs_soff_t off, int whence);

// Truncates the size of the file to the specified size
//
// Returns a negative error code on failure.
int fs_file_truncate( lfs_file_t *file, lfs_off_t size);

// Return the position of the file
//
// Equivalent to lfs_file_seek(lfs, file, 0, LFS_SEEK_CUR)
// Returns the position of the file, or a negative error code on failure.
lfs_soff_t fs_file_tell( lfs_file_t *file);

// Change the position of the file to the beginning of the file
//
// Equivalent to lfs_file_seek(lfs, file, 0, LFS_SEEK_SET)
// Returns a negative error code on failure.
int fs_file_rewind( lfs_file_t *file);

// Return the size of the file
//
// Similar to lfs_file_seek(lfs, file, 0, LFS_SEEK_END)
// Returns the size of the file, or a negative error code on failure.
lfs_soff_t fs_file_size( lfs_file_t *file);


/// Directory operations ///

// Create a directory
//
// Returns a negative error code on failure.
int fs_mkdir( const char *path);

// Open a directory
//
// Once open a directory can be used with read to iterate over files.
// Returns a negative error code on failure.
int fs_dir_open( lfs_dir_t *dir, const char *path);

// Close a directory
//
// Releases any allocated resources.
// Returns a negative error code on failure.
int fs_dir_close( lfs_dir_t *dir);

// Read an entry in the directory
//
// Fills out the info structure, based on the specified file or directory.
// Returns a positive value on success, 0 at the end of directory,
// or a negative error code on failure.
int fs_dir_read( lfs_dir_t *dir, struct lfs_info *info);

// Change the position of the directory
//
// The new off must be a value previous returned from tell and specifies
// an absolute offset in the directory seek.
//
// Returns a negative error code on failure.
int fs_dir_seek( lfs_dir_t *dir, lfs_off_t off);

// Return the position of the directory
//
// The returned offset is only meant to be consumed by seek and may not make
// sense, but does indicate the current position in the directory iteration.
//
// Returns the position of the directory, or a negative error code on failure.
lfs_soff_t fs_dir_tell( lfs_dir_t *dir);

// Change the position of the directory to the beginning of the directory
//
// Returns a negative error code on failure.
int fs_dir_rewind( lfs_dir_t *dir);


/// Filesystem-level filesystem operations

// Finds the current size of the filesystem
//
// Note: Result is best effort. If files share COW structures, the returned
// size may be larger than the filesystem actually is.
//
// Returns the number of allocated blocks, or a negative error code on failure.
lfs_ssize_t fs_size();

// Traverse through all blocks in use by the filesystem
//
// The provided callback will be called with each block address that is
// currently in use by the filesystem. This can be used to determine which
// blocks are in use or how much of the storage is available.
//
// Returns a negative error code on failure.
int fs_traverse( int (*cb)(void*, lfs_block_t), void *data);

#endif
