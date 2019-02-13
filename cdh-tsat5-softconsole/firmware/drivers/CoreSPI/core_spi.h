/*******************************************************************************
 * (c) Copyright 2008 Actel Corporation.  All rights reserved.
 * 
 * CoreSPI public API.
 *
 * SVN $Revision: 1550 $
 * SVN $Date: 2009-10-22 16:12:09 +0100 (Thu, 22 Oct 2009) $
 */
#ifndef CORE_SPI_H_
#define CORE_SPI_H_

#include "cpu_types.h"

/*******************************************************************************
 * The CoreSPI can operate in either slave or master mode.
 * Aside from the base address of your CoreSPI instance, the SPI_init function
 * expects to be given one of these values to indicate its mode.
 */
typedef enum SPI_mode_t
{
	/** When enabled, the CoreSPI will be in SLAVE mode: */
	SPI_MODE_SLAVE		= 0,

	/** When enabled, the CoreSPI will be in MASTER mode: */
	SPI_MODE_MASTER		= 1
} SPI_mode_t;

/*******************************************************************************
 *
 */
typedef enum __SPI_protocol_mode_t
{
    SPI_MODE0 = 0x00,
    SPI_MODE1 = 0x10,
    SPI_MODE2 = 0x08,
    SPI_MODE3 = 0x18
} SPI_protocol_mode_t;


/*******************************************************************************
 * SPI transfer order, MSB first or LSB first
 */
typedef enum __SPI_order_t
{
    SPI_MSB_FIRST = 0x00,
    SPI_LSB_FIRST = 0x20
} SPI_order_t;



/*******************************************************************************
 * SPI interrupt mode, enable or disable
 */
typedef enum __SPI_int_mode_t
{ 
    SPI_INT_DISABLE = 0x00,
    SPI_INT_ENABLE  =0x80
} SPI_int_mode_t;


/*******************************************************************************
 * SPI error status
 */
typedef enum __SPI_err_t
{
    SPI_ERR_CLEAR = 0,
    SPI_ERR_SET = 1
} SPI_err_t;


/*******************************************************************************
 * Serial clock selection.
 * The CoreSPI serial clock frequency is the APB bus clock speed divided down.  
 * Used as parameter to functions SPI_init(), SPI_configure() and SPI_set_clk()
 * to set the clock divider used to generate the SPI serial clock.
 */
 typedef enum __SPI_pclk_div_t
 {
	PCLK_DIV_2		= 0,
	PCLK_DIV_4		= 1,
	PCLK_DIV_8		= 2,
	PCLK_DIV_16		= 3,
	PCLK_DIV_32		= 4,
	PCLK_DIV_64		= 5,
	PCLK_DIV_128	= 6,
	PCLK_DIV_256	= 7
} SPI_pclk_div_t;

/*******************************************************************************
 * SPI_slave_t provides the constants for a master to choose a specific slave
 * with the SPI_slave_select() and SPI_configure() functions.
 */
 typedef enum __SPI_slave_t
 {
	SPI_SLAVE_0		= 0x01, 
	SPI_SLAVE_1		= 0x02,
	SPI_SLAVE_2		= 0x04,
	SPI_SLAVE_3		= 0x08,
	SPI_SLAVE_4		= 0x10,
	SPI_SLAVE_5		= 0x20,
	SPI_SLAVE_6		= 0x40,
	SPI_SLAVE_7		= 0x80
} SPI_slave_t;

#define MAX_SPI_SLAVES 0x08

/*******************************************************************************
 * device control parameters for slave devices 
 * 
 *  devControl is the Control Register 1 configuration for the specific SPI port
 *  devValid is the valid flag for the configuration
 */

typedef struct __SPI_device_params_t
{
	uint8_t devControl;
	uint8_t devValid;
} SPI_device_params_t;

#define VALID_SLAVE_CFG 0x5A



/*******************************************************************************
 * SPI_xfer_errs_t is the enum for SPI transfer errors
 */
 typedef enum __SPI_xfer_errs_t
 {
	XFER_ERR_NONE               = 0x00,  
	XFER_ERR_NO_COUNT			= 0x01,
	XFER_ERR_NULL_SEND_BUFFER 	= 0x02,
	XFER_ERR_CLR_RX_BUFFER      = 0x03,
	XFER_ERR_SPI_WRITE          = 0x04,
	XFER_ERR_SPI_READ           = 0x05	
	
} SPI_xfer_errs_t;

/*******************************************************************************
 * SPI_instance_t
 * 
 * There should be one instance of this structure for each instance of SPI
 * in your system. SPI_init routine initializes this structure. It is used to 
 * identify the various SPIs in your system and an initilized CoreSPI instance's 
 * structure should be passed as first parameter to CoreSPI functions to identify 
 * which CoreSPI should perform the requested operation.
 * Software, using this driver should only need to create one single instance of 
 * this data structure for each CoreSPI instance in the system.
 */
typedef struct __SPI_instance_t
{
	/** Base address in the processor's memory map for the
	 * registers of the CoreSPI instance being initialised. */
	addr_t base_addr;

    /* slave port configurations */
    SPI_device_params_t slave_config[MAX_SPI_SLAVES];

} SPI_instance_t;

/*******************************************************************************
 * SPI_init() initializes the CoreSPI hardware instance identified with the
 * first parameter. This function should be called before any other CoreSPI API
 * functions are called.
 *
 * @param this_spi      Pointer to a SPI_instance_t structure identifying the
 *                      CoreSPI hardware instance to be initialised.
 *
 * @param base_address	The base_address parameter is the base address of the
 *                      CoreSPI	hardware instance in the processor's memory map.
 *
 * @param master_p      Required mode of operation. Allowed values are:
 * 						    - SPI_MODE_MASTER
 *						    - SPI_MODE_SLAVE
 * @param SPI_protocol  Required protocol of operation. Allowed values are
 * 						    - SPI_MODE0 (0x00)
 * 						    - SPI_MODE1 (0x10)
 * 						    - SPI_MODE2 (0x08)
 * 						    - SPI_MODE3 (0x18)
 *
 * @param clk_rate      Divider value used to generate serial interface clock
 *                      signal from PCLK. Allowed values are:
 *	                        - PCLK_DIV_2
 *	                        - PCLK_DIV_4
 *	                        - PCLK_DIV_8
 *	                        - PCLK_DIV_16
 *	                        - PCLK_DIV_32
 *	                        - PCLK_DIV_64
 *	                        - PCLK_DIV_128
 *	                        - PCLK_DIV_256
 */
void SPI_init
(
	SPI_instance_t * this_spi,
	addr_t base_address,
	SPI_mode_t master_p,
    SPI_protocol_mode_t protocol_mode,
    SPI_pclk_div_t clk_rate
);

/*******************************************************************************
 * SPI_slave_select() is used by the Master to select a specific
 * slave using the slave select register.
 * 
 * @param this_spi      Pointer to a SPI_instance_t structure
 * @param slave         Eight bits masked to select the slave.
 * 
 */
void SPI_slave_select
(
	SPI_instance_t * this_spi,
	SPI_slave_t slave
);


/*******************************************************************************
 * The SPI_block_read() function generates SPI bus transactions where a command
 * is first sent to the slave device before data is read from the slave.
 * The total length of the SPI transaction is the number of bytes of the command
 * plus the number of bytes read from the slave.
 * This function is only meant to be used by SPI masters.
 *
 * @param this_spi      Pointer to a SPI_instance_t structure identifying the
 *                      CoreSPI hardware instance used by the function.
 *
 * @param cmd_buffer    The cmd_buffer parameter is a pointer to a buffer
 *                      containing the command to be transmited over the SPI bus.
 *
 * @param cmd_byte_size The cmd_byte_size parameter contains the length of the
 *                      command in bytes.
 *
 * @param rd_buffer     The rd_buffer parameter is a pointer to the buffer where
 *                      the data read from the slave will be stored.
 *
 * @param rd_byte_size  The rd_byte_size parameter contains the size in bytes of
 *                      the read buffer.
 */
void SPI_block_read
(
    SPI_instance_t * this_spi,
    uint8_t * cmd_buffer,
    size_t cmd_byte_size,
    uint8_t * rd_buffer,
    size_t rd_byte_size
);

/*******************************************************************************
 * The SPI_block_write() function generates bus transactions where a command is
 * first sent to the slave before data is written to the slave.
 * The total length of the SPI transaction is the number of bytes of the command
 * plus the number of bytes written to the slave.
 * This function is only meant to be used by SPI masters.
 *
 * @param this_spi      Pointer to a SPI_instance_t structure identifying the
 *                      CoreSPI hardware instance used by the function.
 *
 * @param cmd_buffer    The cmd_buffer parameter is a pointer to a buffer
 *                      containing the command to be transmited over the SPI bus.
 *
 * @param cmd_byte_size The cmd_byte_size parameter contains the length of the
 *                      command in bytes.
 *
 * @param wr_buffer     The wd_buffer parameter is a pointer to the buffer
 *                      containing the data to write to the slave.
 *
 * @param wr_byte_size  The wd_byte_size parameter contains the size in bytes of
 *                      the write buffer.
 */
void SPI_block_write
(
    SPI_instance_t * this_spi,
    uint8_t * cmd_buffer,
    size_t cmd_byte_size,
    uint8_t * wr_buffer,
    size_t wr_byte_size
);

/*******************************************************************************
 * SPI_set_port() is used to set an SPI instance to a specific Core address
 * slave using the slave select register.
 * 
 * @param this_spi       Pointer to a SPI_instance_t structure
 * @param SPI_base_addr  Core address
 * 
 */
void SPI_set_port
(
    SPI_instance_t * this_spi,
	addr_t SPI_base_addr
);

/*******************************************************************************
 * SPI_enable() enables an SPI core
 *  
 * @param this_spi       Pointer to a SPI_instance_t structure 
 *  
 */
void SPI_enable
(
    SPI_instance_t * this_spi
);


/*******************************************************************************
 * SPI_disable() disables an SPI core
 * 
 * @param this_spi   Pointer to a SPI_instance_t structure
 * 
 */
void SPI_disable
(
    SPI_instance_t * this_spi
);


/*******************************************************************************
 * SPI_set_mode() sets the required opeation mode - master or slave
 *  
 * @param this_spi   Pointer to a SPI_instance_t structure
 * @param SPI_mode   Required mode of operation. Allowed values are:
 * 						- SPI_MODE_MASTER
 *						- SPI_MODE_SLAVE
 * 
 */
void SPI_set_mode
(
    SPI_instance_t * this_sp,
	SPI_mode_t SPI_mode
);

/*******************************************************************************
 * SPI_set_protocol() sets the required protocol mode
 * 
 * @param this_spi      Pointer to a SPI_instance_t structure
 * @param SPI_protocol  Required protocol of operation. Allowed values are
 * 						 -SPI_MODE0 (0x00)
 * 						 -SPI_MODE1 (0x10)
 * 						 -SPI_MODE2 (0x08)
 * 						 -SPI_MODE3 (0x18)
 * 
 */
void SPI_set_protocol
(
    SPI_instance_t * this_spi,
	SPI_protocol_mode_t SPI_protocol
);

/*******************************************************************************
 * SPI_set_order sets the required order of data transfer 
 * 
 * @param this_spi     Pointer to a SPI_instance_t structure
 * @param SPI_order    Required order of data transfer. Allowed values are:
 * 						- SPI_MSB_FIRST (0x00)
 * 						- SPI_LSB_FIRST (0x20)
 * 
 */

void SPI_set_order
(
    SPI_instance_t * this_spi,
	SPI_order_t SPI_order
);

/*******************************************************************************
 * SPI_set_clk sets the required clock divider value 
 * 
 * @param this_spi     Pointer to a SPI_instance_t structure
 * @param SPI_clk      Required clock divider. Allowed values are:
 * 						- PCLK_DIV_2   (0)
 * 						- PCLK_DIV_4   (1)
 * 						- PCLK_DIV_8   (2)
 * 						- PCLK_DIV_16  (3)
 * 						- PCLK_DIV_32  (4)
 * 						- PCLK_DIV_64  (5)
 * 						- PCLK_DIV_128 (6)
 * 						- PCLK_DIV_256 (7)
 * 
 */
void SPI_set_clk
(
    SPI_instance_t * this_spi,
    SPI_pclk_div_t SPI_clk
);

/*******************************************************************************
 * SPI_err_check returns the SPI error status 
 * 
 * @param this_spi    Pointer to a SPI_instance_t structure 
 * 
 */

SPI_err_t SPI_err_check
(
    SPI_instance_t * this_spi
);


/*******************************************************************************
 * SPI_status() returns the SPI status (busy, Tx status, Rx status)
 * 
 * @param this_spi    Pointer to a SPI_instance_t structure  
 * 
 */

uint8_t SPI_status
(
    SPI_instance_t * this_spi
);


/*******************************************************************************
 * SPI_write_byte() transmits a byte on the SPI interface
 * 
 * @param this_spi        Pointer to a SPI_instance_t structure  
 * @param SPI_write_data  Data byte to write
 * 
 */
SPI_err_t SPI_write_byte
(
    SPI_instance_t * this_spi,
    uint8_t * SPI_write_data
);


/*******************************************************************************
 * SPI_read_byte() reads a byte from the SPI interface
 * 
 * @param this_spi       Pointer to a SPI_instance_t structure  
 * @param SPI_read_data  Data byte to read
 * 
 */
SPI_err_t SPI_read_byte
(
    SPI_instance_t * this_spi,
    uint8_t * SPI_read_data
);


/*******************************************************************************
 *   SPI_configure() configures specific communication paramaters for a slave
 *                   device by storing the paramaters in an indexed array in the 
 *                   SPI instance 
 * 
 * @param this_spi         Pointer to a SPI_instance_t structure  
 * @param slave            Slave number (0-7)  
 * @param protocol_mode    Required protocol to communicate with this slave  
 * @param clk_rate         Required clock divider rate for this slave 
 * @param data_xfer_order  Data transfer order for this slave
 *   
 */
void SPI_configure
(
    SPI_instance_t * this_spi,
    SPI_slave_t slave,
    SPI_protocol_mode_t protocol_mode,
    SPI_pclk_div_t clk_rate,
    SPI_order_t data_xfer_order
);


/*******************************************************************************
 * SPI_transfer() transmits and receives data on the SPI interface
 * 
 * @param this_spi          Pointer to a SPI_instance_t structure 
 * @param send_buffer       Address of the transmit buffer 
 * @param receive_buffer    Address of the receive buffer 
 * @param byte_count        Size in bytes to transfer 
 *  
 */
SPI_xfer_errs_t SPI_transfer
(
    SPI_instance_t * this_spi,
    uint8_t * send_buffer,
    uint8_t * receive_buffer,
    uint8_t byte_count
);


/*******************************************************************************
 * SPI_set_int() enables or disables Core SPI interrupts
 * 
 * @param this_spi       Pointer to a SPI_instance_t structure  
 * @param int_mode       mode (1=enable, 0=disable)
 * 
 */
void SPI_set_int
(
    SPI_instance_t * this_spi,
    SPI_int_mode_t int_mode
);


#endif /*CORE_SPI_H_*/
