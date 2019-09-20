/*******************************************************************************
 * (c) Copyright 2008 Actel Corporation.  All rights reserved.
 * 
 * CoreSPI bare metal driver implementation.
 *
 * SVN $Revision: 1550 $
 * SVN $Date: 2009-10-22 16:12:09 +0100 (Thu, 22 Oct 2009) $
 */

#include "core_spi.h"
#include "corespi_regs.h"
#include "hal.h"

/*******************************************************************************
 * 
 */
void SPI_init
(
	SPI_instance_t * this_spi,
	addr_t base_addr,
	SPI_mode_t master_p,
    SPI_protocol_mode_t protocol_mode,
    SPI_pclk_div_t clk_rate
)
{
	uint8_t ctrl1;
	uint8_t ctrl2 = CTRL2_EN_BIT_MASK;
    uint8_t i;
	
	this_spi->base_addr = base_addr;

    for ( i = 0; i < MAX_SPI_SLAVES; ++i )
    {
        this_spi->slave_config[i].devValid = 0;
    }
    
	ctrl1 = protocol_mode | clk_rate;	
	if ( SPI_MODE_MASTER == master_p )
	{
		ctrl1 |= MODE_BIT_MASK;
	}
	else 
	{
        ctrl1 &= ~MODE_BIT_MASK;
	}
		
	HAL_set_8bit_reg( this_spi->base_addr, CTRL1, ctrl1 );
	HAL_set_8bit_reg( this_spi->base_addr, CTRL2, ctrl2 );
}

/*******************************************************************************
 *  SPI_slave_select
 * 
 *  This function selects a slave channel. If a specific SPI configuration 
 *  has been stored in the SPI instance for this port then configure the 
 *  CoreSPI for the required mode of operation
 *  
 */
void SPI_slave_select
(
	SPI_instance_t * this_spi,
	SPI_slave_t slave
)
{
	uint8_t arrPos=0;
	uint8_t ctrl1;
	
	/* select the slave channel */
	
	HAL_set_8bit_reg( this_spi->base_addr, SLAVE_SEL, slave );
	
	
	/* if this slave has a valid configuration entry in this SPI
	 * instance structure then configure the SPI to reflect the
	 * required config */ 
	
	/* set index */
	while(slave >>= 1) ++arrPos;
	
	if(this_spi->slave_config[arrPos].devValid==VALID_SLAVE_CFG)		
			
	{
		/* get the current CTRL1 and preserve ints and mode_select */
         ctrl1 = HAL_get_8bit_reg( this_spi->base_addr, CTRL1 );
		 ctrl1&= (MODE_BIT_MASK|CTRL1_IE_BIT_MASK);
       
       /* set the required parameters for this slave */
		 ctrl1 |= (this_spi->slave_config[arrPos].devControl);
		 HAL_set_8bit_reg(this_spi->base_addr, CTRL1, ctrl1 );				
	}
	
}

/*******************************************************************************
 * SPI_block_read
 * 
 */
void SPI_block_read
(
    SPI_instance_t * this_spi,
    uint8_t * cmd_buffer,
    size_t cmd_byte_size,
    uint8_t * rd_buffer,
    size_t rd_byte_size
)
{
    uint16_t transfer_idx = 0;
    int32_t tx_idx;
    int32_t rx_idx;
    uint32_t rx_raw;
    uint32_t status;
    uint32_t tx_empty;
    uint32_t rx_data_ready;
    
    uint32_t transfer_size = 0;     /* Total number of bytes transfered. */
    
    /* Compute number of bytes to transfer. */
    transfer_size = cmd_byte_size + rd_byte_size;
    
    /* Flush the receive FIFO. */
    
    status = HAL_get_8bit_reg( this_spi->base_addr, STATUS );
    rx_data_ready = status & STATUS_RX_DATA_RDY_BIT_MASK;
    while ( rx_data_ready )
    {
        rx_raw = HAL_get_8bit_reg( this_spi->base_addr, DATA );
        status = HAL_get_8bit_reg( this_spi->base_addr, STATUS );
        rx_data_ready = status & STATUS_RX_DATA_RDY_BIT_MASK;
    }
    
    /**/
    tx_idx = 0;
    rx_idx = 0;
    while ( transfer_idx < transfer_size )
    {
        /* Get FIFOs status. */
        status = HAL_get_8bit_reg( this_spi->base_addr, STATUS );
        tx_empty = status & STATUS_TX_EMPTY_BIT_MASK;
        rx_data_ready = status & STATUS_RX_DATA_RDY_BIT_MASK;
        
        if ( rx_data_ready )
        {
            rx_raw = HAL_get_8bit_reg( this_spi->base_addr, DATA );
            if ( transfer_idx >= cmd_byte_size )
            {
                if ( rx_idx < rd_byte_size )
                {
                    rd_buffer[rx_idx] = (uint8_t)rx_raw;   
                }
                rx_idx++;
            }
            transfer_idx++;
        }
        
        if ( tx_empty )
        {
            if ( tx_idx < cmd_byte_size )
            {
                HAL_set_8bit_reg( this_spi->base_addr, DATA, cmd_buffer[tx_idx++] );
            }
            else
            {
                if ( tx_idx < transfer_size )
                {
                    HAL_set_8bit_reg( this_spi->base_addr, DATA, 0x00 );
                    tx_idx++;
                }
            }
        }
    }
    
}

/*******************************************************************************
 * SPI_block_write
 * 
 */
void SPI_block_write
(
    SPI_instance_t * this_spi,
    uint8_t * cmd_buffer,
    size_t cmd_byte_size,
    uint8_t * wr_buffer,
    size_t wr_byte_size
)
{
    uint32_t cmd_tx_idx;
    uint32_t data_tx_idx;
    int32_t tx_idx;
    int32_t rx_idx;
    uint32_t rx_raw;
    uint32_t status;
    uint32_t tx_empty;
    uint32_t rx_data_ready;
    
    uint32_t transfer_size = 0;     /* Total number of bytes transfered. */
    
    /* Compute number of bytes to transfer. */
    transfer_size = cmd_byte_size + wr_byte_size;

    /* Flush the receive FIFO. */
    status = HAL_get_8bit_reg( this_spi->base_addr, STATUS );
    rx_data_ready = status & STATUS_RX_DATA_RDY_BIT_MASK;
    while ( rx_data_ready )
    {
        rx_raw = HAL_get_8bit_reg( this_spi->base_addr, DATA );
        status = HAL_get_8bit_reg( this_spi->base_addr, STATUS );
        rx_data_ready = status & STATUS_RX_DATA_RDY_BIT_MASK;
    }
    
    /**/
    cmd_tx_idx = 0;
    data_tx_idx = 0;
    tx_idx = 0;
    rx_idx = 0;
    while ( rx_idx < transfer_size )
    {
        /* Get FIFOs status. */
        status = HAL_get_8bit_reg( this_spi->base_addr, STATUS );
        tx_empty = status & STATUS_TX_EMPTY_BIT_MASK;
        rx_data_ready = status & STATUS_RX_DATA_RDY_BIT_MASK;
        
        if ( rx_data_ready )
        {
            rx_raw = HAL_get_8bit_reg( this_spi->base_addr, DATA );
            rx_idx++;
        }
        
        if ( tx_empty )
        {
            if ( tx_idx < cmd_byte_size )
            {
                HAL_set_8bit_reg( this_spi->base_addr, DATA, cmd_buffer[cmd_tx_idx++] );
                tx_idx++;
            }
            else if ( tx_idx < transfer_size )
            {
                HAL_set_8bit_reg( this_spi->base_addr, DATA, wr_buffer[data_tx_idx++] );
                tx_idx++;
            }
            else
            {
                /* Do nothing we are waiting for the last byte to be transfered. */
            }
        }
    }
    
}

/*******************************************************************************
 * SPI_set_port
 * 
 * Set the instance address to the required CoreSPI address
 * 
 */
void SPI_set_port
(
    SPI_instance_t * this_spi,
	addr_t SPI_base_addr
)

{
	
	this_spi->base_addr = SPI_base_addr;	
}

/*******************************************************************************
 * SPI_enable
 * 
 * Enable the SPI interface, clear the error bit and set the enable 
 * bit in the instance to indicate that this SPI instance is enabled
 *
 */

void SPI_enable
(
    SPI_instance_t * this_spi
)
 
{
    uint8_t ctrl2Data=CTRL2_EN_BIT_MASK;
    HAL_set_8bit_reg(this_spi->base_addr, CTRL2, ctrl2Data );
}

/*******************************************************************************
 *
 * SPI_disable
 * 
 * Disable the SPI interface, clear the error bit and clear the enable
 * bit in the SPI instance
 *
 */

void SPI_disable
(
    SPI_instance_t * this_spi
)

{
    uint8_t ctrl2Data=0;
    HAL_set_8bit_reg(this_spi->base_addr, CTRL2, ctrl2Data );
}

/*******************************************************************************
 * SPI_set_mode
 * 
 * Set the required SPI mode (Master or Slave) and set the selected 
 * mode in the SPI instance
 *
 */

void SPI_set_mode
(
    SPI_instance_t * this_spi,
    SPI_mode_t SPI_mode

)

{
    /* get the current value for control register1 */
    uint8_t ctrl1 = HAL_get_8bit_reg(this_spi->base_addr, CTRL1);
	
    /* set the required mode and status */
    if (SPI_mode==SPI_MODE_MASTER)
    {
    	ctrl1 |= MODE_BIT_MASK;
        HAL_set_8bit_reg(this_spi->base_addr, CTRL1, ctrl1 );
    }
    else
   {
        ctrl1 &= !MODE_BIT_MASK;
        HAL_set_8bit_reg(this_spi->base_addr, CTRL1, ctrl1 );
    }
}

/*******************************************************************************
 * SPI_set_protocol
 * 
 * Set the required protocol mode by setting the clock phase(CPHA) and clock 
 * polarity(CPOL) bits. Set the new protocol mode in the SPI instance structure
 * 
 */

void SPI_set_protocol
(
    SPI_instance_t * this_spi,
    SPI_protocol_mode_t SPI_protocol
)

{
	uint8_t ctrl1;
    ctrl1 = HAL_get_8bit_reg(this_spi->base_addr, CTRL1);

    /* clear the CPOL and CPHA */       
    ctrl1 &= ~(CPOL_BIT_MASK|CPHA_BIT_MASK);
	
    /* set the required CPOL and CPHA */
    ctrl1 |= SPI_protocol;

    HAL_set_8bit_reg(this_spi->base_addr, CTRL1, ctrl1 );
}

/*******************************************************************************
 * SPI_set_order
 * 
 * Set the order of transfer (LSB or MSB first)
 *
 */
void SPI_set_order
(
    SPI_instance_t * this_spi,
    SPI_order_t SPI_order
)

{
    uint8_t ctrl1 = HAL_get_8bit_reg(this_spi->base_addr, CTRL1);

    /* clear the order bit */
    ctrl1 &= ~(ORDER_BIT_MASK);

    /* set the required order */
    ctrl1 |=SPI_order;
    HAL_set_8bit_reg(this_spi->base_addr, CTRL1, ctrl1 );
}


/*******************************************************************************
 * SPI_set_clk
 * 
 * Set the clock divider value
 *
 */
void SPI_set_clk
(
    SPI_instance_t * this_spi,
    SPI_pclk_div_t SPI_clk
)
{
	 uint8_t ctrl1; 
	 ctrl1= HAL_get_8bit_reg(this_spi->base_addr, CTRL1);

	 ctrl1&= ~SCKS_BIT_MASK;
	 
	 ctrl1|=SPI_clk;
	 HAL_set_8bit_reg(this_spi->base_addr, CTRL1, ctrl1 );
	 
}

/*******************************************************************************
 * SPI_err_check
 * 
 * Check for error conditions (RX receiver overrun error) 
 *
 */

SPI_err_t SPI_err_check
(
    SPI_instance_t * this_spi
)

{
    uint8_t errStat;
    errStat = HAL_get_8bit_reg(this_spi->base_addr, STATUS );
    if (errStat & ERROR_BIT_MASK)
	    return SPI_ERR_SET;
    else return SPI_ERR_CLEAR;
}


/*******************************************************************************
 * SPI_status
 * 
 * Returns the SPI status bits 
 * 
 */
uint8_t SPI_status
(
    SPI_instance_t * this_spi
)

{ 
    uint8_t spiStat;
    spiStat = HAL_get_8bit_reg(this_spi->base_addr, STATUS );
	
    spiStat&=(!ERROR_BIT_MASK);
	return spiStat;
}

/*******************************************************************************
 * SPI_write_byte
 * 
 * Transmit a byte of data on the SPI interface
 * 
 */
SPI_err_t SPI_write_byte
(
    SPI_instance_t * this_spi,
    uint8_t  * SPI_write_data
)
 
{
	uint8_t txEmpty;

	txEmpty=HAL_get_8bit_reg(this_spi->base_addr,STATUS);
    txEmpty&=STATUS_TX_EMPTY_BIT_MASK;

	if(txEmpty)
	{
		HAL_set_8bit_reg(this_spi->base_addr,DATA, *SPI_write_data);
		return SPI_ERR_CLEAR;
	}
	else return SPI_ERR_SET;

}	

/*******************************************************************************
 * SPI_read_byte
 * 
 * Read a byte from the SPI interface
 * 
 */

SPI_err_t SPI_read_byte
(
    SPI_instance_t * this_spi,
	uint8_t  * SPI_read_data
)

{
    uint8_t rxReady;
	rxReady=HAL_get_8bit_reg(this_spi->base_addr,STATUS);
	rxReady&=STATUS_RX_DATA_RDY_BIT_MASK;

	if(rxReady)
	{
		*SPI_read_data=HAL_get_8bit_reg(this_spi->base_addr,DATA);
		return SPI_ERR_CLEAR;
	}
    else return SPI_ERR_SET;
}

/*******************************************************************************
 * SPI_configure
 * 
 * Configure the communication parameters for a specific slave device. This 
 * function receives configuration parameters for a slave device and saves 
 * the values in the SPI instance at the slave_config index for this slave
 * device(0-7). When this slave device is selected (SPI_slave_select) the SPI 
 * core is re-configured from the saved settings.
 * This function is only meant to be used for CoreSPI instances configured as
 * master.
 *  
 */
void SPI_configure
(
    SPI_instance_t * this_spi,
    SPI_slave_t slave,
    SPI_protocol_mode_t protocol_mode,
    SPI_pclk_div_t clk_rate,
    SPI_order_t data_xfer_order
)

{
	uint8_t ctrl1;
	uint8_t arrPos=0;
	
	ctrl1 = HAL_get_8bit_reg( this_spi->base_addr, CTRL1 );
	
	/* maintain the current interrupt and master/slave setting */
	
	ctrl1&=(MODE_BIT_MASK|CTRL1_IE_BIT_MASK);
	ctrl1|= (data_xfer_order|protocol_mode|clk_rate);
	      
    /* index into the array */
	while(slave >>= 1) ++arrPos;
	
	/* save this slaves config values and set valid entry */
	this_spi->slave_config[arrPos].devControl = ctrl1;
	this_spi->slave_config[arrPos].devValid=VALID_SLAVE_CFG;	
}

/*******************************************************************************
 * SPI_transfer
 * 
 * This function transmit and receives SPI data buffers. Data to be transmitted
 * from the SPI is passed in sendBuffer and received data is transferred to 
 * receiveBuffer. The buffers can be used as follows:
 * 
 * send_buffer, receive_buffer => different send and receive buffers
 * send_buffer, send_buffer, => send buffer is used for both send and receive
 * send_buffer, NULL => the receive data is discarded
 * receive_buffer, receive_buffer  => the send data is not relevant
 * 
 */
SPI_xfer_errs_t SPI_transfer
(
    SPI_instance_t * this_spi,
    uint8_t * send_buffer,
    uint8_t * receive_buffer,
    uint8_t byte_count
)
    
{	
	/* internal buffers */
	uint8_t * intSendBuffer;
	uint8_t * intRecBuffer;
	uint8_t tempBuf[byte_count];
	
    /* master or slave */
    SPI_mode_t MSMode;
    
    uint8_t ctrl1;	 
    uint8_t rawData;
    uint8_t xferByte=0;
	
    /* local null pointer def */    
    uint8_t * NULL=0;  
    
    /* basic checks on the input parameters */
    if(byte_count<=0)
      return XFER_ERR_NO_COUNT;
  
    if(send_buffer==NULL)
      return XFER_ERR_NULL_SEND_BUFFER;  
    
    /* setup the buffers based on the input paramaters */
    intSendBuffer=send_buffer;
    intRecBuffer=receive_buffer;
    
    /* receive data not returned - local buffer */
    if(receive_buffer==NULL)
       intRecBuffer=tempBuf;    	   
    	   
    /* check if configured as master or slave */
  
    ctrl1 = HAL_get_8bit_reg(this_spi->base_addr, CTRL1);
    if(ctrl1 & MODE_BIT_MASK)
    	MSMode=SPI_MODE_MASTER;
    else MSMode=SPI_MODE_SLAVE;    
    
    /* if master mode then transmit and receive data */
    
    if (MSMode==SPI_MODE_MASTER)
    {    	
   	/* clear the receive buffer */       
        while(SPI_status(this_spi)& STATUS_RX_DATA_RDY_BIT_MASK)
    	{
    	    if (SPI_read_byte(this_spi,&rawData))
    	        return XFER_ERR_CLR_RX_BUFFER;
    	}    	
    	xferByte=0;
    	while(byte_count)
        {
    		if (SPI_write_byte(this_spi,&intSendBuffer[xferByte]))
    			return XFER_ERR_SPI_WRITE;
    		if (SPI_read_byte(this_spi,&intRecBuffer[xferByte]))
    			return XFER_ERR_SPI_READ;
    		xferByte++;
    		byte_count--;  	  	
        }   	
    }
        
    /* in slave mode wait for data by polling the receive buffer  */
    if( MSMode==SPI_MODE_SLAVE)
        {    	
        xferByte=0;
    	while(byte_count)
    	{
    		/* poll the receive buffer for data */
    	    while(!(SPI_status(this_spi)& STATUS_RX_DATA_RDY_BIT_MASK))
            {
    		   ;
    	    }   	   
    	   
            if (SPI_read_byte(this_spi,&intRecBuffer[xferByte]))
                return XFER_ERR_SPI_READ;
            if (SPI_write_byte(this_spi,&intSendBuffer[xferByte]))
    	     	return XFER_ERR_SPI_WRITE;
    	    xferByte++;
    	    byte_count--;  		           	 
        }
    }
    return XFER_ERR_NONE;    
}
    

/*******************************************************************************
 * SPI_set_int
 * 
 * Set the interrupt mode
 * 
 * Enable=1
 * Disable=0
 *
 */
void SPI_set_int
(
    SPI_instance_t * this_spi,
    SPI_int_mode_t int_mode
) 
{
	 uint8_t ctrl1; 
	 ctrl1= HAL_get_8bit_reg(this_spi->base_addr, CTRL1);

	 ctrl1&= ~CTRL1_IE_BIT_MASK;
	 
	 ctrl1|=int_mode;
	 HAL_set_8bit_reg(this_spi->base_addr, CTRL1, ctrl1 );
	 
}


