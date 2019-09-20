//-----------------------------------------------------------------------------
// (c) Copyright 2007 Actel Corporation
//
// name:		corespi.v
// function:	Top-level CoreSPI (Serial Peripheral Interface) with APB I/F
// comments:	best viewed with tabstops set to "4", all port signals are
//				active high, unless otherwise noted
// history:		3/15/07  - AS created
//
// Rev:			2.1 15Mar107 AS - Production
//
//-----------------------------------------------------------------------------
module CORESPI #(
parameter FAMILY = 17,
parameter USE_MASTER = 1,
parameter USE_SLAVE	= 1
)(
  // clocks and resets
  input PCLK,
  input PRESETN, 
  // serial interface
  output m_sck, 
  input m_miso, 
  output m_mosi, 
  output [7:0] m_ss, 
  input s_sck, 
  output s_miso,
  input s_mosi, 
  input s_ss, 
  // operation mode indicator signals
  output enable_master, 
  output enable_slave, 
  // interrupt signals
  output interrupt, 
  output tx_reg_empty, 
  output rx_data_ready,
  // APB slave I/F
  input  PSEL,
  input  PENABLE,
  input  PWRITE,
  input  [3:0] PADDR,
  input  [7:0] PWDATA,
  output [7:0] PRDATA
);

// SFR interface signals
wire  [7:0] cpu_data_in;
wire  [7:0] cpu_data_out;
wire  [1:0] cpu_addr_bus;
wire        cpu_we;
wire        cpu_re;

assign cpu_we = (PWRITE && PSEL && PENABLE);
assign cpu_re = (~PWRITE && PSEL && PENABLE);
assign cpu_data_in = PWDATA;
assign PRDATA = cpu_data_out;
assign cpu_addr_bus = PADDR[3:2];


CORESPI_SFR #(
  .USE_MASTER(USE_MASTER),
  .USE_SLAVE(USE_SLAVE)  
) ucorespi_sfr (
  .sysclk(PCLK), 
  .nreset(PRESETN), 
  .m_sck(m_sck), 
  .m_miso(m_miso), 
  .m_mosi(m_mosi), 
  .m_ss(m_ss), 
  .s_sck(s_sck), 
  .s_miso(s_miso),
  .s_mosi(s_mosi), 
  .s_ss(s_ss), 
  .enable_master(enable_master), 
  .enable_slave(enable_slave),
  // CPU I/F:
  .data_in(cpu_data_in), 
  .data_out(cpu_data_out), 
  .addrbus(cpu_addr_bus), 
  .we(cpu_we), 
  .re(cpu_re),
  // Interrupts
  .interrupt(interrupt), 
  .tx_reg_empty(tx_reg_empty), 
  .rx_data_ready(rx_data_ready)
  );


endmodule
