//-----------------------------------------------------------------------------
// (c) Copyright 2005 Actel Corporation
//
// name:		spi_slave.v
// function:	SPI (Serial Peripheral Interface) Slave
// comments:	best viewed with tabstops set to "4"
// history:		8/01/03  - TFB created
//				2/07/04  - TFB modified count_en logic slightly
//				3/18/04  - TFB changed reset name to nreset, changed error
//				name to rx_error, other minor cleanups
//
// Rev:			2.1 24Jan05 TFB - Production
//
//-----------------------------------------------------------------------------

`timescale 1ns / 1ps

module spi_slave (sysclk, nreset, enable, sck, miso, mosi, ss, cpol, cpha,
rx_data_reg, rx_data_ready, rx_reg_re, tx_data_reg, tx_reg_we, tx_reg_empty,
clear_error, rx_error);

// control signals
input			sysclk;	// Global clock
input			nreset;	// Act.low asynchronous reset
input			enable;	// Synchronous Enable
// SPI interface signals
input			sck;	// SPI Serial Clock signal
output			miso;	// SPI master input/slave output signal
input			mosi;	// SPI master output/slave input signal
input			ss;		// SPI slave select output
// SPI Slave internal signals
input			cpol;	// SPI Serial Clock Polarity
input			cpha;	// SPI Serial Clock Phase
output	[7:0]	rx_data_reg;	// Rx data register
output			rx_data_ready;	// Status signal: rx data ready to read
input			rx_reg_re;		// Read Enable for rx_data_reg
input	[7:0]	tx_data_reg;	// Tx data register
input			tx_reg_we;		// Write enable for tx data register
output			tx_reg_empty;	// Status signal: tx reg can be written
input			clear_error;	// Syncronous reset for clearing rx error
output			rx_error; 

// internal signals
wire			miso;
wire			rx_data_ready;
wire			rx_error;
reg		[7:0]	rx_data_reg;
reg				tx_reg_empty;
reg				i_sck;
reg				d_sck;
reg				i_mosi;
reg				t_mosi;
reg				i_ss;
reg				t_ss;
reg				di_ss;
reg		[7:0]	rxtx_shift_reg;
wire			rx_ready;
reg				rx_data_waiting;
reg				rx_error_i;
reg		[3:0]	count;
reg				count_en;

    //----------------------------------------------
    // Synchronize SPI interface input signals with
    // the system clock to avoid metastability problems.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            i_sck <= 1'b0 ; 
            d_sck <= 1'b0 ; 
            i_mosi <= 1'b0 ; 
            t_mosi <= 1'b0 ; 
            i_ss <= 1'b1 ; 
            t_ss <= 1'b1 ; 
        end
        else
        begin
            if (enable == 1'b1)
            begin
                t_mosi <= mosi ; 
                t_ss <= ss ; 
                if (cpol == 1'b0 & cpha == 1'b0)
                begin
                    i_sck <= sck ; 
                end
                else if (cpol == 1'b0 & cpha == 1'b1)
                begin
                    i_sck <= ~sck ; 
                end
                else if (cpol == 1'b1 & cpha == 1'b0)
                begin
                    i_sck <= ~sck ; 
                end
                else
                begin
                    i_sck <= sck ; 
                end 
                d_sck <= i_sck ; 
                i_mosi <= t_mosi ; 
                i_ss <= t_ss ; 
            end
            else
            begin
                t_ss <= 1'b1 ; 
            end 
        end 
    end 

    //-----------------------------------------
    // Receive / Transmit Data Shift register.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            rxtx_shift_reg <= {8{1'b0}} ; 
            count_en <= 1'b0 ; 
        end
        else
        begin
            // TFB 2/7/04
            //count_en <= '0';
            if (i_ss == 1'b1)
            begin
                rxtx_shift_reg <= tx_data_reg ; 
            end
            else if (i_sck == 1'b1 & d_sck == 1'b0)
            begin
                rxtx_shift_reg[0] <= i_mosi ; 
                rxtx_shift_reg[7:1] <= rxtx_shift_reg[6:0] ; 
            end
            // TFB 2/7/04
            //count_en <= '1'; 
            // TFB added 2/7/04
            if (i_sck == 1'b1 & d_sck == 1'b0 & i_ss == 1'b0)
            begin
                count_en <= 1'b1 ; 
            end
            else
            begin
                count_en <= 1'b0 ; 
            end 
        end 
    end 
    assign miso = rxtx_shift_reg[7] ;

    //-------------------------------
    // Count shift cycles.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            count <= 4'b0000 ; 
        end
        else
        begin
            if (i_ss == 1'b1 | count == 4'b1000)
            begin
                count <= 4'b0000 ; 
            end
            else if (count_en == 1'b1)
            begin
                count <= count + 4'b0001 ; 
            end 
        end 
    end 
    assign rx_ready = count[3] & (~count[2]) & (~count[1]) & (~count[0]) ;

    //-----------------------------
    // Generate TX_reg_empty flag.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            tx_reg_empty <= 1'b1 ; 
            di_ss <= 1'b0 ; 
        end
        else
        begin
            if (i_ss == 1'b0 & di_ss == 1'b1)
            begin
                tx_reg_empty <= 1'b1 ; 
            end
            else if (tx_reg_we == 1'b1)
            begin
                tx_reg_empty <= 1'b0 ; 
            end 
            di_ss <= i_ss ; 
        end 
    end 
    //-----------------------------
    // Generate RX_data_ready flag.
    assign rx_data_ready = rx_data_waiting ;

    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            rx_data_waiting <= 1'b0 ; 
            rx_error_i <= 1'b0 ; 
        end
        else
        begin
            if (clear_error == 1'b1)
            begin
                rx_data_waiting <= 1'b0 ; 
                rx_error_i <= 1'b0 ; 
            end
            else if (rx_ready == 1'b1)
            begin
                if (rx_data_waiting == 1'b1)
                begin
                    rx_error_i <= 1'b1 ; 
                end 
                rx_data_waiting <= 1'b1 ; 
            end
            else if (rx_reg_re == 1'b1)
            begin
                rx_data_waiting <= 1'b0 ; 
            end 
        end 
    end 
    assign rx_error = rx_error_i ;

    //------------------------------------------------
    // Transfer received data from the shift register
    // to the receive data register.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            rx_data_reg <= 8'b00000000 ; 
        end
        else
        begin
            if (enable == 1'b1)
            begin
                if (rx_ready == 1'b1)
                begin
                    rx_data_reg <= rxtx_shift_reg ; 
                end 
            end 
        end 
    end 
endmodule
