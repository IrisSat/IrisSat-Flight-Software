//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  Header file for the AS3016204 mram.
//
// History
// 2021-03-25 by Joseph Howarth
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


#ifndef AS3016204_MRAM_H_
#define AS3016204_MRAM_H_
#include <stdint.h>

//Memory Parameters
#define AS_MAX_MRAM_ADDR    (0x1FFFFF)

void asMram_init();

void asMram_read(   uint32_t address,       // The starting address to read from.
                    uint8_t * rd_buffer,    // The buffer to place the read data into.
                    uint32_t rd_buffer_size   // The size of the read buffer.
                    );

void asMram_write(  uint32_t address,       // The starting address to write to.
                    uint8_t * wr_buffer,    // The buffer containing the data to write.
                    uint32_t wr_buffer_size   // The size of the write buffer.
                    );




#endif /* AS3016204_MRAM_H_ */
