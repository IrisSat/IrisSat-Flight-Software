#ifndef SOFTWARE_UPDATE_H_
#define SOFTWARE_UPDATE_H_
//------------------------------------------------------------------------------
// File Description:
//  Driver for updating the software/FPGA fabric (ISP).
//
// History
// 2020-05-05 by Joseph Howarth
// - Created.
//------------------------------------------------------------------------------

#include <stdint.h>

// TODO: Need to update these!
#define FIRMWARE_GOLDEN_ADDRESS	0x000100
#define FIRMWARE_UPDATE_ADDRESS 0x100000


void authenticate_firmware(uint8_t version);
void initiate_firmware_update(uint8_t version);
void save_program(void * buff, uint16_t size, uint8_t version);//version = 0 for golden image, version = 1 for updated image.
void repeat_program();
void set_program_size(uint32_t size,uint8_t version);

#endif
