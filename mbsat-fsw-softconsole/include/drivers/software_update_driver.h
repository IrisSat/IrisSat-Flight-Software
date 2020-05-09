#ifndef SOFTWARE_UPDATE_H_
#define SOFTWARE_UPDATE_H_
//------------------------------------------------------------------------------
//
// Repository:
//	Github: https://github.com/joehowarth17/ManitobaSat-Flight-Software
//
// File Description:
//  Driver for updating the software/FPGA fabric (ISP).
//
// History
// 2020-05-05 by Joseph Howarth
// - Created.
//------------------------------------------------------------------------------

#include <stdint.h>

// TODO: Need to update these!
#define FIRMWARE_GOLDEN_ADDRESS	0x000000
#define FIRMWARE_UPDATE_ADDRESS 0x000000


void authenticate_firmware(uint32_t addr);
void initiate_firmware_update(uint32_t addr);
void save_program(void * buff, uint16_t size);
void repeat_program();
void set_program_size(uint32_t size);

#endif
