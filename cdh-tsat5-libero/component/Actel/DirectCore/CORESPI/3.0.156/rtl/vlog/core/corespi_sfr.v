//-----------------------------------------------------------------------------
// (c) Copyright 2005 Actel Corporation
//
// name:		corespi_sfr.v
// function:	CoreSPI (Serial Peripheral Interface) with SFR (special function 
//            register) interface
// comments:	best viewed with tabstops set to "4", all port signals are
//				active high, unless otherwise noted
// history:		8/01/03  - TFB created
//				3/18/04  - TFB changed reset name to nreset, changed error
//				name to rx_error, other minor cleanups
//
// Rev:			2.1 24Jan05 TFB - Production
//
//-----------------------------------------------------------------------------

`timescale 1ns / 1ps

module CORESPI_SFR #(
parameter USE_MASTER	= 1,
parameter USE_SLAVE		= 1
)
(sysclk, nreset, m_sck, m_miso, m_mosi, m_ss, s_sck, s_miso,
s_mosi, s_ss, enable_master, enable_slave, data_in, data_out, addrbus, we, re,
interrupt, tx_reg_empty, rx_data_ready);

// master+slave	: set USE_MASTER=1, USE_SLAVE=1 (default)
// master only	: set USE_MASTER=1, USE_SLAVE=0
// slave only	: set USE_MASTER=0, USE_SLAVE=1


input			sysclk;			// Global clock
input			nreset;			// Act.low asynchronous reset
// SPI interface signals
output			m_sck;			// SPI master generated Serial Clock
input			m_miso;			// SPI serial data (master in/slave out)
output			m_mosi;			// SPI serial data (master out/slave in)
// SPI master generated slave select lines
output	[7:0]	m_ss;
input			s_sck;			// SPI slave, Serial Clock input
output			s_miso;			// SPI serial data (master in/slave out)
input			s_mosi;			// SPI serial data (master out/slave in)
input			s_ss;			// SPI slave, act.low slave select input
output			enable_master;	// CoreSPI operating in master mode
output			enable_slave;	// CoreSPI operating in slave mode
// generic microcontroller interface signals
input	[7:0]	data_in;		// Input data bus
output	[7:0]	data_out;		// Output data bus
input	[1:0]	addrbus;		// Address bus
input			we;				// Write enable
input			re;				// Read enable
output			interrupt;		// Masked interrupt output
// Unmasked interrupt outputs
output			tx_reg_empty;	// transmit register empty
output			rx_data_ready;

wire			m_sck;
wire			m_mosi;
wire	[7:0]	m_ss;
wire			s_miso;
wire			enable_master;
wire			enable_slave;
wire	[7:0]	data_out;
wire			interrupt;
wire			tx_reg_empty;
wire			rx_data_ready;

wire			cpol;
wire			cpha;
wire			control_we;
wire			control_re;
wire			control2_we;
reg		[7:0]	control_reg;
wire	[7:0]	status_reg;
wire			status_re;
wire			ss_reg_we;
wire			ss_reg_re;
wire			tx_reg_we;
wire			rx_reg_re;
reg				i_enable_spi;
wire	[2:0]	scksel;
wire			spi_ordr;
wire			spi_ms;
wire			spi_ie;
wire	[7:0]	i_rx_data_reg;
wire	[7:0]	rx_data_reg_m;
wire	[7:0]	rx_data_reg_s;
wire	[7:0]	lsb_rx_data_reg;
wire			rx_data_ready_m;
wire			i_rx_data_ready;
wire			rx_data_ready_s;
reg		[7:0]	tx_data_reg;
wire			i_tx_reg_empty;
wire			tx_reg_empty_m;
wire			tx_reg_empty_s;
wire			master_busy;
reg				clear_error;
wire			m_rx_error;
wire			s_rx_error;
wire			rx_error;
wire			m_enable;
wire			s_enable;
reg		[7:0]	ss_reg;
wire			m_ss_int;
wire			gnd8;


	assign gnd8				= 8'b0;

    //-----------------------
    // I/O Port assignments.
    assign enable_master	= m_enable ;
    assign enable_slave		= s_enable ;
    assign tx_reg_empty		= i_tx_reg_empty ;
    assign rx_data_ready	= i_rx_data_ready ;

    // TFB 2/8/04, these are static high, if slave-only is used ...
    //   m_ss(0)	<= m_ss_int or (not ss_reg(0));
    //   m_ss(1)	<= m_ss_int or (not ss_reg(1));
    //   m_ss(2)	<= m_ss_int or (not ss_reg(2));
    //   m_ss(3)	<= m_ss_int or (not ss_reg(3));
    //   m_ss(4)	<= m_ss_int or (not ss_reg(4));
    //   m_ss(5)	<= m_ss_int or (not ss_reg(5));
    //   m_ss(6)	<= m_ss_int or (not ss_reg(6));
    //   m_ss(7)	<= m_ss_int or (not ss_reg(7));

    //--------------------
    // Address Decoder
    //--------------------
    // write transmit data register
    assign tx_reg_we	= (we == 1'b1 & addrbus == 2'b00) ? 1'b1 : 1'b0 ;
    // read receive data register
    assign rx_reg_re	= (re == 1'b1 & addrbus == 2'b00) ? 1'b1 : 1'b0 ;
    // write control register
    assign control_we	= (we == 1'b1 & addrbus == 2'b01) ? 1'b1 : 1'b0 ;
    // read control register
    assign control_re	= (re == 1'b1 & addrbus == 2'b01) ? 1'b1 : 1'b0 ;
    // write 2nd control register
    assign control2_we	= (we == 1'b1 & addrbus == 2'b10) ? 1'b1 : 1'b0 ;
    // read status register
    assign status_re	= (re == 1'b1 & addrbus == 2'b10) ? 1'b1 : 1'b0 ;
    // write slave select register
    assign ss_reg_we	= (we == 1'b1 & addrbus == 2'b11) ? 1'b1 : 1'b0 ;
    // read slave select register
    assign ss_reg_re	= (re == 1'b1 & addrbus == 2'b11) ? 1'b1 : 1'b0 ;

    //--------------------
    // Write Control reg.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            control_reg	<= {8{1'b0}} ;
        end
        else
        begin
            if (control_we == 1'b1)
            begin
                control_reg	<= data_in ;
            end
        end
    end

    //-----------------------
    // Control register bits
    //-----------------------
    // control_reg(2:0) - Clock selector:
    // 000 = /2   | 010 = /8   | 100 = /32  | 110 = /128
    // 001 = /4   | 011 = /16  | 101 = /64  | 111 = /256
    assign scksel[0]	= control_reg[0] ;
    assign scksel[1]	= control_reg[1] ;
    assign scksel[2]	= control_reg[2] ;
    // clock polarity (0 = active high, 1 = active low)
    assign cpol			= control_reg[3] ;
    // clock phase (0 = 0 degree delay, 1 = 90 degree delay)
    assign cpha			= control_reg[4] ;
    // Select data transfer order (1 = LSB first, 0 = MSB first)
    assign spi_ordr		= control_reg[5] ;
	// master or slave select (1 = master, 0 = slave)
	generate
	if (USE_MASTER==1 & USE_SLAVE==1)
	begin
		assign spi_ms		= control_reg[6] ;
	end
	endgenerate
	// for master only implementation, static high
	generate
	if (USE_MASTER==1 & USE_SLAVE==0)
	begin
		assign spi_ms		= 1'b1 ;
	end
	endgenerate
	// for slave only implementation, static low
	generate
	if (USE_MASTER==0 & USE_SLAVE==1)
	begin
		assign spi_ms		= 1'b0 ;
	end
	endgenerate
    // Interrupt enable (1 = enable interrupts, 0 = disable interrupts)
    assign spi_ie		= control_reg[7] ;

    //----------------------
    // Write Control reg 2.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            clear_error		<= 1'b0 ;
            i_enable_spi	<= 1'b0 ;
        end
        else
        begin
            if (control2_we == 1'b1)
            begin
                clear_error		<= data_in[0] ;
                i_enable_spi	<= data_in[7] ;
            end
            else if (clear_error == 1'b1)
            begin
                clear_error		<= 1'b0 ;
            end
        end
    end

    //-------------------
    // Read operations.
    assign data_out				=	(rx_reg_re == 1'b1 & spi_ordr == 1'b0)	?
									i_rx_data_reg							: 
									(rx_reg_re == 1'b1 & spi_ordr == 1'b1)	?
									lsb_rx_data_reg							:
									(control_re == 1'b1)	? control_reg	:
									(status_re == 1'b1)		? status_reg	:
									(ss_reg_re == 1'b1)		? ss_reg		:
									{8{1'b0}} ;

    assign i_rx_data_reg		= (m_enable == 1'b1) ?	rx_data_reg_m		:
														rx_data_reg_s ;

    assign status_reg[0]		= rx_error ;
    assign status_reg[1]		= i_rx_data_ready ;
    assign status_reg[2]		= i_tx_reg_empty ;
    // SPI master is busy transmitting byte
    assign status_reg[3]		= (spi_ms == 1'b1) ? master_busy : 1'b0 ;
    assign status_reg[6:4]		= 3'b000 ;
    assign status_reg[7]		= i_enable_spi ;

    assign rx_error				= m_rx_error | s_rx_error ;

    // flip order for LSB first operation
    assign lsb_rx_data_reg[0]	= i_rx_data_reg[7] ;
    assign lsb_rx_data_reg[1]	= i_rx_data_reg[6] ;
    assign lsb_rx_data_reg[2]	= i_rx_data_reg[5] ;
    assign lsb_rx_data_reg[3]	= i_rx_data_reg[4] ;
    assign lsb_rx_data_reg[4]	= i_rx_data_reg[3] ;
    assign lsb_rx_data_reg[5]	= i_rx_data_reg[2] ;
    assign lsb_rx_data_reg[6]	= i_rx_data_reg[1] ;
    assign lsb_rx_data_reg[7]	= i_rx_data_reg[0] ;

    //--------------------
    // tx data reg.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            tx_data_reg	<= {8{1'b0}} ;
        end
        else
        begin
            if (tx_reg_we == 1'b1)
            begin
                if (spi_ordr == 1'b0)
                begin
                    tx_data_reg	<= data_in ;
                end
                else
                begin
                    tx_data_reg[0]	<= data_in[7] ;
                    tx_data_reg[1]	<= data_in[6] ;
                    tx_data_reg[2]	<= data_in[5] ;
                    tx_data_reg[3]	<= data_in[4] ;
                    tx_data_reg[4]	<= data_in[3] ;
                    tx_data_reg[5]	<= data_in[2] ;
                    tx_data_reg[6]	<= data_in[1] ;
                    tx_data_reg[7]	<= data_in[0] ;
                end
            end
        end
    end

    //-----------------------
    // interrupt generation.
    assign interrupt		=	i_enable_spi &
								(spi_ie & (i_tx_reg_empty | i_rx_data_ready)) ;

    assign i_tx_reg_empty	=	(m_enable == 1'b1)	?	tx_reg_empty_m		:
								(s_enable == 1'b1)	?	tx_reg_empty_s		:
								1'b0 ;
    assign i_rx_data_ready	=	(m_enable == 1'b1)	?	rx_data_ready_m		:
								(s_enable == 1'b1)	?	rx_data_ready_s		:
								1'b0 ;

	generate
	if (USE_MASTER==1)
	begin
		//--------------------------------------------------
		// slave select lines. (not used in slave-only mode)
		always @(posedge sysclk or negedge nreset)
		begin
			if (nreset == 1'b0)
				ss_reg	<= {8{1'b0}} ;
			else
			begin
				if (ss_reg_we == 1'b1)
					ss_reg	<= data_in ;
			end
		end
		//----------------------------------------
		// instantiation of SPI master
		spi_master u_master (
			.sysclk(sysclk),
			.nreset(nreset),
			.enable(m_enable),
			.sck(m_sck),
			.miso(m_miso),
			.mosi(m_mosi),
			.ss(m_ss_int),
			.cpol(cpol),
			.cpha(cpha),
			.clocksel(scksel),
			.rx_data_reg(rx_data_reg_m),
			.rx_data_ready(rx_data_ready_m),
			.rx_reg_re(rx_reg_re),
			.tx_data_reg(tx_data_reg),
			.tx_reg_empty(tx_reg_empty_m),
			.busy(master_busy),
			.tx_reg_we(tx_reg_we),
			.clear_error(clear_error),
			.rx_error(m_rx_error)
		);
		// TFB 2/8/04
		assign m_ss[0]	= m_ss_int | (~ss_reg[0]) ;
		assign m_ss[1]	= m_ss_int | (~ss_reg[1]) ;
		assign m_ss[2]	= m_ss_int | (~ss_reg[2]) ;
		assign m_ss[3]	= m_ss_int | (~ss_reg[3]) ;
		assign m_ss[4]	= m_ss_int | (~ss_reg[4]) ;
		assign m_ss[5]	= m_ss_int | (~ss_reg[5]) ;
		assign m_ss[6]	= m_ss_int | (~ss_reg[6]) ;
		assign m_ss[7]	= m_ss_int | (~ss_reg[7]) ;
	end
	endgenerate
	generate
	if (USE_MASTER==0)
	begin
		always @(gnd8)
			ss_reg	<= gnd8;
		assign m_sck			= 1'b0 ;
		assign m_mosi			= 1'b0 ;
		assign m_ss_int			= 1'b0 ;
		assign rx_data_reg_m	= 8'b00000000 ;
		assign rx_data_ready_m	= 1'b0 ;
		assign tx_reg_empty_m	= 1'b0 ;
		assign master_busy		= 1'b0 ;
		assign m_rx_error		= 1'b0 ;
		// TFB 2/8/04, these are static high, if slave-only is used ...
		assign m_ss				= 8'b11111111 ;
	end
	endgenerate

    assign m_enable			= i_enable_spi & spi_ms ;

	generate
	if (USE_SLAVE==1)
	begin
		//----------------------------------------
		// instantiation of SPI slave
		spi_slave u_slave (
			.sysclk(sysclk),
			.nreset(nreset),
			.enable(s_enable),
			.sck(s_sck),
			.miso(s_miso),
			.mosi(s_mosi),
			.ss(s_ss),
			.cpol(cpol),
			.cpha(cpha),
			.rx_data_reg(rx_data_reg_s),
			.rx_data_ready(rx_data_ready_s),
			.rx_reg_re(rx_reg_re),
			.tx_data_reg(tx_data_reg),
			.tx_reg_we(tx_reg_we),
			.tx_reg_empty(tx_reg_empty_s),
			.clear_error(clear_error),
			.rx_error(s_rx_error)
		);
	end
	endgenerate
	generate
	if (USE_SLAVE==0)
	begin
		assign s_miso			= 1'b0 ;
		assign rx_data_reg_s	= 8'b00000000 ;
		assign rx_data_ready_s	= 1'b0 ;
		assign tx_reg_empty_s	= 1'b0 ;
		assign s_rx_error		= 1'b0 ;
	end
	endgenerate

	assign s_enable		= i_enable_spi & (~spi_ms) ;

endmodule
