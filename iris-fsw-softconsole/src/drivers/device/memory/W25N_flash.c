//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// File Description:
//  Source file for external flash memory (W25N01GVxxIG) driver.
//	This driver is a modified version of the Mongoose OS Winbond W25XXX SPI NAND Flash Driver
//	https://github.com/mongoose-os-libs/vfs-dev-w25xxx
//
// History
// 2019-04-17 by Joseph Howarth
// - Created.
// 2020-03-31 by Joseph Howarth
// - Updated to use flash interface.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 * Copyright (c) 2014-2018 Cesanta Software Limited
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


#include "drivers/device/memory/W25N_flash.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// DEFINITIONS AND MACROS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// ENUMS AND ENUM TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTS AND STRUCT TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// TYPEDEFS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This wrapper function is used to get the page number and offset for a given address.
//
// Parameters:
//
//	dd:			This should be a pointer to a FLASH_dev struct, which will be
//					used to refer to the device.
//
//	off:			The address for which the page number and page offset will be calculated.
//
//  page_num: 		A pointer to where the calculated page number will be stored.
//
//	page_off:		A pointer to where the calculated page offset will be stored.
//
// Returns:
//  Returns true if successful, false if not..
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool w25n_map_page(W25NDevice_t *dd, size_t off, uint16_t *page_num, uint16_t *page_off);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function returns the minimum of two numbers.
//
// Parameters:
//
//	arg1:			The first number to compare.
//
//	arg2:			The second number to compare.
//
//  Returns:
//  The lower number.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static size_t MIN(size_t arg1, size_t arg2);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function is used to get the page number and offset for a given address.
//
// Parameters:
//
//	dd:			This should be a pointer to a FLASH_dev struct, which will be
//					used to refer to the device.
//
//	off:			The address for which the page number and page offset will be calculated.
//
//  page_num: 		A pointer to where the calculated page number will be stored.
//
//	page_off:		A pointer to where the calculated page offset will be stored.
//
//  bb_reserve:		The number of reserved blocks.
//
// Returns:
//  Returns true if successful, false if not.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool w25n_map_page_ex(W25NDevice_t *dd, size_t off, uint16_t *page_num,uint16_t *page_off, uint8_t bb_reserve);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function loads one page of data into the flash memory buffer.
//
// Parameters:
//
//	dd:			This should be a pointer to a FLASH_dev struct, which will be
//				used to refer to the device.
//
//	page_num:	The page number that will be loaded into the flash memory buffer.
//
// Returns:
//  Enter description of return values (if any).
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
FlashStatus_t w25n_page_data_read(W25NDevice_t *dd,uint16_t page_num);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function sends a command along with an argument to the flash memory. It will store the response to the command.
//
// Parameters:
//
//	dd:			This should be a pointer to a FLASH_dev struct, which will be
//				used to refer to the device.
//
//	op:			The operation that should be executed by the flash.
//
//	arg_len:	The length of the argument for the command in bytes.
//
//	arg:		The argument for the command.
//
//	dummy_len:	The number of dummy bytes needed for the command.
//
//	rx_len:		Number of bytes to receive in response to command.
//
//	rx:			A pointer where the received bytes will be stored.
//
// Returns:
//  Enter description of return values (if any).
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

static bool w25n_op_arg_rx(W25NDevice_t *dd, W25NOperation_t op,size_t arg_len, uint32_t arg, int dummy_len,size_t rx_len, void *rx_data);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function sends a command along with an argument to the flash memory.
//
// Parameters:
//
//	dd:			This should be a pointer to a FLASH_dev struct, which will be
//				used to refer to the device.
//
//	op:			The operation that should be executed by the flash.
//
//	arg_len:	The length of the argument for the command in bytes.
//
//	arg:		The argument for the command.
//
//
// Returns:
//  Enter description of return values (if any).
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool w25n_op_arg(W25NDevice_t *dd, W25NOperation_t op,size_t arg_len, uint32_t arg);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function reads one of the three status registers.
//
// Parameters:
//
//	dd:			This should be a pointer to a FLASH_dev struct, which will be
//				used to refer to the device.
//
//	reg:		The register to be read.
//
//
//
// Returns:
//  The value of the status register.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint8_t w25n_read_reg(W25NDevice_t *dd,W25NReg_t reg);


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function writes to one of the three status registers.
//
// Parameters:
//
//	dd:			This should be a pointer to a FLASH_dev struct, which will be
//				used to refer to the device.
//
//	reg:		The register to be write.
//
//	value:		The value to write to the register.
//
// Returns:
//  True if successful, false if not.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool w25n_write_reg(W25NDevice_t *dd, W25NReg_t reg,uint8_t value);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function sends a simple command to the flash memory.
//
// Parameters:
//
//	dd:			This should be a pointer to a FLASH_dev struct, which will be
//				used to refer to the device.
//
//	op:			The operation that should be executed by the flash.
//
// Returns:
//  Enter description of return values (if any).
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool w25n_simple_op(W25NDevice_t *dd, W25NOperation_t op);


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function sends a simple command to the flash memory, and receives back data.
//
// Parameters:
//
//	dd:			This should be a pointer to a FLASH_dev struct, which will be
//				used to refer to the device.
//
//	op:			The operation that should be executed by the flash.
//
//	dummy_len:	The number of dummy bytes needed for the command.
//
//	rx_len:		Number of bytes to receive in response to command.
//
//	rx_data:			A pointer where the received bytes will be stored.
//
//
// Returns:
//  Enter description of return values (if any).
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool w25n_simple_rx_op(W25NDevice_t *dd, W25NOperation_t op, int dummy_len, size_t rx_len, void *rx_data);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  This function transmits to the flash over spi.
//
// Parameters:
//
//	dd:			This should be a pointer to a FLASH_dev struct, which will be
//				used to refer to the device.
//
//	tx_len:		The number of bytes to send, excluding dummy bytes..
//
//	tx_data:	A pointer to the data to send.
//
//	dummy_len:	The number of dummy bytes.
//
//	rx_len:		The number of bytes to receive.
//
//	rx_data:	A pointer to where the received data will be stored.
//
// Returns:
//  Always returns true.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool w25n_txn(W25NDevice_t *dd, size_t tx_len,const void *tx_data, int dummy_len, size_t rx_len,void *rx_data);


//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

static bool w25n_map_page(W25NDevice_t *dd, size_t off, uint16_t *page_num, uint16_t *page_off) {

	return w25n_map_page_ex(dd, off, page_num, page_off,dd->bb_reserve);

}

static size_t MIN(size_t arg1, size_t arg2){

	size_t ans;

	if(arg1<arg2){
		ans = arg1;
	}
	else if(arg2<arg1){
		ans = arg2;
	}
	else{
		ans = arg1;
	}
	return ans;
}

static bool w25n_map_page_ex(W25NDevice_t *dd, size_t off,uint16_t *page_num,uint16_t *page_off, uint8_t bb_reserve) {

  bool res = false;
  size_t die_size = W25N_DIE_SIZE;


  die_size -= ((size_t) bb_reserve) * W25N_BLOCK_SIZE;
  if(off>die_size){
	  res = false;
  }
  else{
	  *page_num = off / W25N_PAGE_SIZE;

	  if (page_off != NULL) *page_off = off % W25N_PAGE_SIZE;

	  res = true;
  }

  return res;
}

static bool w25n_op_arg_rx(W25NDevice_t *dd, W25NOperation_t op,size_t arg_len, uint32_t arg, int dummy_len,size_t rx_len, void *rx_data) {

	uint8_t buf[5] = {op};
  size_t tx_len;
  switch (arg_len) {
    case 0:
      tx_len = 1;
      break;
    case 1:
      buf[1] = (arg & 0xff);
      tx_len = 2;
      break;
    case 2:
      buf[1] = ((arg >> 8) & 0xff);
      buf[2] = (arg & 0xff);
      tx_len = 3;
      break;
    case 3:
      buf[1] = ((arg >> 16) & 0xff);
      buf[2] = ((arg >> 8) & 0xff);
      buf[3] = (arg & 0xff);
      tx_len = 4;
      break;
    default:
      return false;
  }
  return w25n_txn(dd, tx_len, buf, dummy_len, rx_len, rx_data);
}

static bool w25n_op_arg(W25NDevice_t *dd, W25NOperation_t op,size_t arg_len, uint32_t arg) {

	return w25n_op_arg_rx(dd, op, arg_len, arg, 0, 0, NULL);
}

FlashStatus_t w25n_page_data_read(W25NDevice_t *dd,uint16_t page_num) {

	uint8_t st;

	if (!w25n_op_arg(dd, W25N_OP_PAGE_DATA_READ, 1 + 2, page_num)) {
		return FLASH_ERROR;
	}

	while ((st = w25n_read_reg(dd, W25N_REG_STAT)) & W25N_REG_STAT_BUSY) {
	}

	if (dd->ecc_chk) {

		st = w25n_read_reg(dd, W25N_REG_STAT);

		if (st & (W25N_REG_STAT_ECC1 | W25N_REG_STAT_ECC0)) {

			bool hard = (st & W25N_REG_STAT_ECC1);

			if (hard){
				return FLASH_ERROR_ECC;
			}else{
				return FLASH_ERROR_ECC;
			}
		}
	}

	return FLASH_OK;
}

static uint8_t w25n_read_reg(W25NDevice_t *dd,W25NReg_t reg) {

  uint8_t reg_addr = reg, reg_value = 0;
  w25n_op_arg_rx(dd, W25N_OP_READ_REG, 1, reg_addr, 0, 1, &reg_value);

  return reg_value;
}

static bool w25n_write_reg(W25NDevice_t *dd, W25NReg_t reg,uint8_t value) {

  return w25n_op_arg(dd, W25N_OP_WRITE_REG, 2,(((uint32_t) reg) << 8 | value));
}

static bool w25n_txn(W25NDevice_t *dd, size_t tx_len,const void *tx_data, int dummy_len, size_t rx_len,void *rx_data) {


	size_t total_len_tx = tx_len+dummy_len;
	uint8_t command_buffer[total_len_tx];

	const uint8_t *p = tx_data;

	//Create one command buffer with both the command and the dummy bytes.
	int i;
	for(i=0;i<total_len_tx;i++){

		if(i<tx_len){
			command_buffer[i] = *p;
		}
		else{

			command_buffer[i] = 0;
		}
		p++;
	}

	dd->spi_read(command_buffer,total_len_tx,rx_data,rx_len);

  return true;
}

static bool w25n_simple_rx_op(W25NDevice_t *dd, W25NOperation_t op,
                                int dummy_len, size_t rx_len, void *rx_data) {
  return w25n_txn(dd, 1, &op, dummy_len, rx_len, rx_data);
}

static bool w25n_simple_op(W25NDevice_t *dd, W25NOperation_t op) {
  return w25n_txn(dd, 1, &op, 0, 0, NULL);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

FlashStatus_t w25n_read(W25NDevice_t *dev, size_t address, size_t len, void *dst) {

  FlashStatus_t res = FLASH_ERROR;
  FlashStatus_t res2 = FLASH_ERROR;


  const size_t orig_len = len;

  uint8_t *dp = (uint8_t *) dst;


  uint16_t page_num, page_off;

  while (len > 0) {

    if (!w25n_map_page(dev, address, &page_num, &page_off)) {
      res = FLASH_INVALID_ADDRESS;
      return res;
    }
    size_t rd_len = MIN(len, W25N_PAGE_SIZE - page_off);


    if ((res2 = w25n_page_data_read(dev, page_num))) {
      res = res2;
      return res;
    }
    if (!w25n_op_arg_rx(dev, W25N_OP_READ, 2, page_off, 1, rd_len, dp)) {
      return res;
    }
    address += rd_len;
    len -= rd_len;
    dp += rd_len;
  }
  res = FLASH_OK;

  return res;
}

FlashStatus_t w25n_write(W25NDevice_t *dd,size_t address, size_t len,const void *src) {


  FlashStatus_t res = FLASH_ERROR;
  FlashStatus_t res2;

  const size_t orig_off = address;
  const size_t orig_len = len;

  const uint8_t *dp = (const uint8_t *) src;
  uint8_t die_num;
  uint16_t page_num, page_off;

  while (len > 0) {
    if (!w25n_map_page(dd, address, &page_num, &page_off)) {
      res = FLASH_INVALID_ADDRESS;
      goto out;
    }
    uint8_t txn_buf[3 + 128], st;
    size_t wr_len = MIN(len, W25N_PAGE_SIZE - page_off);

    /* When modifying part of a page, read it first to ensure correct ECC. */
    if (wr_len != W25N_PAGE_SIZE) {
      if ((res2 = w25n_page_data_read(dd, page_num)) != 0) {
        res = res2;
        goto out;
      }
      txn_buf[0] = W25N_OP_PROG_RAND_DATA_LOAD;
    } else {
      txn_buf[0] = W25N_OP_PROG_DATA_LOAD;
    }
    if (!w25n_simple_op(dd, W25N_OP_WRITE_ENABLE)) goto out;

    for (size_t txn_off = 0, txn_len = 0; txn_off < wr_len; txn_off += txn_len) {

      txn_len = MIN(128, wr_len - txn_off);

      txn_buf[1] = (page_off + txn_off) >> 8;
      txn_buf[2] = (page_off + txn_off) & 0xff;

      memcpy(txn_buf + 3, dp, txn_len);

      if (!w25n_txn(dd, 3 + txn_len, txn_buf, 0, 0, NULL)) goto out;
      txn_buf[0] = W25N_OP_PROG_RAND_DATA_LOAD;
      dp += txn_len;
    }
    if (!w25n_op_arg(dd, W25N_OP_PROG_EXECUTE, 1 + 2, page_num)) goto out;
    while ((st = w25n_read_reg(dd, W25N_REG_STAT)) & W25N_REG_STAT_BUSY) {
    }
    if (st & W25N_REG_STAT_PFAIL) {

      /* TODO(rojer): On-the-fly remapping of bad blocks. */
      goto out;
    }
    address += wr_len;
    len -= wr_len;
  }
  res = FLASH_OK;
out:

  (void) orig_off;
  (void) orig_len;
  return res;
}

FlashStatus_t w25n_erase_blocks(W25NDevice_t *dd, size_t block_num, size_t num_blocks) {

 FlashStatus_t res = FLASH_ERROR;

  const size_t total_blocks = W25N_DIE_SIZE/W25N_BLOCK_SIZE - dd->bb_reserve;

  //Check that the block number is valid.
  if(/* block_num < 0 || */ block_num > total_blocks){

	    res = FLASH_INVALID_ADDRESS;
	    return res;
  }

  if( num_blocks> (total_blocks-block_num)){

	    res = FLASH_INVALID_ADDRESS;
	    return res;
  }

  size_t off = block_num * W25N_BLOCK_SIZE;
  size_t len = num_blocks * W25N_BLOCK_SIZE;

    if (off % W25N_BLOCK_SIZE != 0 || len % W25N_BLOCK_SIZE != 0) {
      res = FLASH_INVALID_ADDRESS;
      return res;
    }

  uint16_t page_num;
  uint16_t page_off;

  while (len > 0) {
    if (!w25n_map_page(dd, off, &page_num, &page_off)) {
      res = FLASH_INVALID_ADDRESS;
      return res;
    }

    if (!w25n_simple_op(dd, W25N_OP_WRITE_ENABLE)) return res;
    if (!w25n_op_arg(dd, W25N_OP_BLOCK_ERASE, 1 + 2, page_num)) return res;
    uint8_t st;
    while ((st = w25n_read_reg(dd, W25N_REG_STAT)) & W25N_REG_STAT_BUSY) {
    }
    if (st & W25N_REG_STAT_EFAIL) {
       /* TODO(rojer): On-the-fly remapping of bad blocks. */
      return res;
    }
    off += W25N_BLOCK_SIZE;
    len -= W25N_BLOCK_SIZE;
  }
  res = FLASH_OK;

  return res;
}


FlashStatus_t w25n_dev_init(W25NDevice_t * dev, uint8_t bb_reserve, W25NEccCheck_t ecc_check){

	FlashStatus_t result = FLASH_ERROR;

	dev->size = W25N_DIE_SIZE;

	dev->ecc_chk = ecc_check;
	dev->bb_reserve = bb_reserve;

	W25NOperation_t command = W25N_OP_READ_JEDEC_ID;
	uint8_t id_buffer[3];

	w25n_txn(dev,1,&command,1,3,id_buffer);
	if(id_buffer[0] == W25N_ID_1 && id_buffer[1] == W25N_ID_2 && id_buffer[2] == W25N_ID_3){

		result = FLASH_OK;
	}

	 int num_bb = 0;
	 uint8_t cfg0 = 0u;
	 for (uint8_t i = 0; i < 1; i++) {

	   w25n_write_reg(dev, W25N_REG_PROT, 0);
	   w25n_write_reg(dev, W25N_REG_CONF,
	                     cfg0 | W25N_REG_CONF_ECCE | W25N_REG_CONF_BUF);

	 }

	 if (dev->bb_reserve > 0) {
	   dev->size -= ((size_t) 1 * dev->bb_reserve * W25N_BLOCK_SIZE);
	 }


	return result;
}

FlashStatus_t w25n_read_bb_lut(W25NDevice_t *dd,
                               W25NBadBlockLUT_t *lut, int *num_bb) {
  FlashStatus_t res = FLASH_ERROR;
  uint8_t tmp[W25N_BB_LUT_SIZE * 4];
  if (!w25n_op_arg_rx(dd, W25N_OP_BBM_READ_LUT, 0, 0, 1, sizeof(tmp),
                        tmp)) {
    return res;
  }
  for (int i = 0, j = 0; j < (int) W25N_BB_LUT_SIZE; i++, j += 4) {
    W25NBadBlockEntry_t *e = &lut->e[i];
    e->enable = !!(tmp[j] & 0x80);
    e->invalid = !!(tmp[j] & 0x40);
    e->lba = (((uint16_t)(tmp[j] & 3)) << 8) | tmp[j + 1];
    e->pba = (((uint16_t) tmp[j + 2]) << 8) | tmp[j + 3];
    if (num_bb != NULL && e->enable && !e->invalid) (*num_bb)++;
  }
  res = FLASH_OK;

  return res;
}


FlashStatus_t w25n_remap_block(W25NDevice_t *dd, size_t bad_off,
                        size_t good_off) {
  FlashStatus_t res = false;

  uint16_t bpn, lba, pba;
  W25NBadBlockLUT_t *lut;
  if (!w25n_map_page_ex(dd, bad_off, &bpn, NULL, false)) {
    return res;
  }
  uint16_t gpn;
  if (!w25n_map_page_ex(dd, good_off,  &gpn, NULL, false)) {
    return res;
  }
  lba = bpn >> 6, pba = gpn >> 6;
  /*
   * The datasheet says:
   *   Registering the same address in multiple PBAs is prohibited.
   *   It may cause unexpected behavior.
   */

  lut = &dd->bb_lut;
  for (int i = 0; i < (int) W25N_BB_LUT_SIZE; i++) {
    if (lut->e[i].lba == lba) {
    	//Mapping already exists.;
      return res;
    }
  }

  if (w25n_read_reg(dd, W25N_REG_STAT) & W25N_REG_STAT_LUTF) {
	 //BB lookup table is full.
    return res;
  }
  {
    uint8_t tx_data[5] = {
        W25N_OP_BBM_SWAP_BLOCKS, (lba >> 8) & 0xff, (lba & 0xff),
        (pba >> 8) & 0xff, (pba & 0xff),
    };
    if (!w25n_simple_op(dd, W25N_OP_WRITE_ENABLE)) return res;
    if (w25n_txn(dd, sizeof(tx_data), tx_data, 0, 0, NULL)) return res;
  }

  if (!w25n_read_bb_lut(dd, lut, NULL)) return res;
  res = FLASH_OK;

  return res;
}
