//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Wed Mar 24 12:21:54 2021
// Version: v12.6 12.900.20.24
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// MSS_C0
module MSS_C0(
    // Inputs
    ADCS_SPI_MISO,
    CAN_RX_F2M,
    DEVRST_N,
    FLASH1_SPI_MISO,
    FLASH2_MISO,
    MMUART_0_RXD_F2M,
    MRAM1_MISO,
    MRAM2_SPI_MISO,
    RTC_SPI_MISO,
    SPI_0_DI,
    // Outputs
    ADCS_SPI_CS,
    ADCS_SPI_MOSI,
    ADCS_SPI_SCK,
    CAN_TX_M2F,
    FLASH1_HOLDn,
    FLASH1_SPI_CS,
    FLASH1_SPI_MOSI,
    FLASH1_SPI_SCK,
    FLASH1_WP,
    FLASH2_CS,
    FLASH2_HOLDn,
    FLASH2_MOSI,
    FLASH2_SCK,
    FLASH2_WP,
    GPIO_0_M2F,
    GPIO_1_M2F,
    GPIO_3_M2F,
    GPIO_5_M2F,
    GPIO_6_M2F,
    GPIO_7_M2F,
    GPIO_8_M2F,
    GPIO_9_M2F,
    MMUART_0_TXD_M2F,
    MRAM1_CS,
    MRAM1_HOLDn,
    MRAM1_MOSI,
    MRAM1_SCK,
    MRAM1_WP,
    MRAM2_HOLDn,
    MRAM2_SPI_CS,
    MRAM2_SPI_MOSI,
    MRAM2_SPI_SCK,
    MRAM2_WP,
    RTC_SPI_CS,
    RTC_SPI_MOSI,
    RTC_SPI_SCK,
    SPI_0_DO,
    // Inouts
    SPI_0_CLK,
    SPI_0_SS0
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  ADCS_SPI_MISO;
input  CAN_RX_F2M;
input  DEVRST_N;
input  FLASH1_SPI_MISO;
input  FLASH2_MISO;
input  MMUART_0_RXD_F2M;
input  MRAM1_MISO;
input  MRAM2_SPI_MISO;
input  RTC_SPI_MISO;
input  SPI_0_DI;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output ADCS_SPI_CS;
output ADCS_SPI_MOSI;
output ADCS_SPI_SCK;
output CAN_TX_M2F;
output FLASH1_HOLDn;
output FLASH1_SPI_CS;
output FLASH1_SPI_MOSI;
output FLASH1_SPI_SCK;
output FLASH1_WP;
output FLASH2_CS;
output FLASH2_HOLDn;
output FLASH2_MOSI;
output FLASH2_SCK;
output FLASH2_WP;
output GPIO_0_M2F;
output GPIO_1_M2F;
output GPIO_3_M2F;
output GPIO_5_M2F;
output GPIO_6_M2F;
output GPIO_7_M2F;
output GPIO_8_M2F;
output GPIO_9_M2F;
output MMUART_0_TXD_M2F;
output MRAM1_CS;
output MRAM1_HOLDn;
output MRAM1_MOSI;
output MRAM1_SCK;
output MRAM1_WP;
output MRAM2_HOLDn;
output MRAM2_SPI_CS;
output MRAM2_SPI_MOSI;
output MRAM2_SPI_SCK;
output MRAM2_WP;
output RTC_SPI_CS;
output RTC_SPI_MOSI;
output RTC_SPI_SCK;
output SPI_0_DO;
//--------------------------------------------------------------------
// Inout
//--------------------------------------------------------------------
inout  SPI_0_CLK;
inout  SPI_0_SS0;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   [0:0]  ADCS_SPI_CS_net_0;
wire          ADCS_SPI_MISO;
wire          ADCS_SPI_MOSI_net_0;
wire          ADCS_SPI_SCK_net_0;
wire          CAN_RX_F2M;
wire          CAN_TX_M2F_net_0;
wire          CoreAPB3_C0_0_APBmslave0_PENABLE;
wire          CoreAPB3_C0_0_APBmslave0_PREADY;
wire          CoreAPB3_C0_0_APBmslave0_PSELx;
wire          CoreAPB3_C0_0_APBmslave0_PSLVERR;
wire          CoreAPB3_C0_0_APBmslave0_PWRITE;
wire          CoreAPB3_C0_0_APBmslave1_PREADY;
wire          CoreAPB3_C0_0_APBmslave1_PSELx;
wire          CoreAPB3_C0_0_APBmslave1_PSLVERR;
wire          CoreAPB3_C0_0_APBmslave2_PREADY;
wire          CoreAPB3_C0_0_APBmslave2_PSELx;
wire          CoreAPB3_C0_0_APBmslave2_PSLVERR;
wire          CoreAPB3_C0_0_APBmslave3_PREADY;
wire          CoreAPB3_C0_0_APBmslave3_PSELx;
wire          CoreAPB3_C0_0_APBmslave3_PSLVERR;
wire          CoreAPB3_C0_0_APBmslave4_PREADY;
wire          CoreAPB3_C0_0_APBmslave4_PSELx;
wire          CoreAPB3_C0_0_APBmslave4_PSLVERR;
wire          CoreAPB3_C0_0_APBmslave5_PREADY;
wire          CoreAPB3_C0_0_APBmslave5_PSELx;
wire          CoreAPB3_C0_0_APBmslave5_PSLVERR;
wire          CoreResetP_C0_0_M3_RESET_N;
wire          CoreResetP_C0_0_MSS_HPMS_READY;
wire          CoreResetP_C0_0_RESET_N_F2M;
wire          CORESPI_C0_0_SPIINT;
wire          CORESPI_C0_0_SPIRXAVAIL;
wire          CORESPI_C0_0_SPITXRFM;
wire          CORESPI_C1_0_SPIINT;
wire          CORESPI_C1_0_SPIRXAVAIL;
wire          CORESPI_C1_0_SPITXRFM;
wire          CORESPI_C1_1_SPIINT;
wire          CORESPI_C1_1_SPIRXAVAIL;
wire          CORESPI_C1_1_SPITXRFM;
wire          CORESPI_C1_2_SPIINT;
wire          CORESPI_C1_2_SPIRXAVAIL;
wire          CORESPI_C1_2_SPITXRFM;
wire          CORESPI_C1_3_SPIINT;
wire          CORESPI_C1_3_SPIRXAVAIL;
wire          CORESPI_C1_3_SPITXRFM;
wire          CORESPI_C1_4_SPIINT;
wire          CORESPI_C1_4_SPIRXAVAIL;
wire          CORESPI_C1_4_SPITXRFM;
wire          DEVRST_N;
wire          FCCC_C0_0_GL0;
wire          FCCC_C0_0_LOCK;
wire          FLASH1_HOLDn_net_0;
wire   [0:0]  FLASH1_SPI_CS_net_0;
wire          FLASH1_SPI_MISO;
wire          FLASH1_SPI_MOSI_net_0;
wire          FLASH1_SPI_SCK_net_0;
wire          FLASH1_WP_net_0;
wire   [0:0]  FLASH2_CS_net_0;
wire          FLASH2_HOLDn_net_0;
wire          FLASH2_MISO;
wire          FLASH2_MOSI_net_0;
wire          FLASH2_SCK_net_0;
wire          FLASH2_WP_net_0;
wire          GPIO_0_M2F_net_0;
wire          GPIO_1_M2F_net_0;
wire          GPIO_3_M2F_net_0;
wire          GPIO_5_M2F_net_0;
wire          GPIO_6_M2F_net_0;
wire          GPIO_7_M2F_net_0;
wire          GPIO_8_M2F_net_0;
wire          GPIO_9_M2F_net_0;
wire          MMUART_0_RXD_F2M;
wire          MMUART_0_TXD_M2F_net_0;
wire   [0:0]  MRAM1_CS_net_0;
wire          MRAM1_HOLDn_net_0;
wire          MRAM1_MISO;
wire          MRAM1_MOSI_net_0;
wire          MRAM1_SCK_net_0;
wire          MRAM1_WP_net_0;
wire          MRAM2_HOLDn_net_0;
wire   [0:0]  MRAM2_SPI_CS_net_0;
wire          MRAM2_SPI_MISO;
wire          MRAM2_SPI_MOSI_net_0;
wire          MRAM2_SPI_SCK_net_0;
wire          MRAM2_WP_net_0;
wire   [31:0] MSS_C0_MSS_0_FIC_0_APB_MASTER_PADDR;
wire          MSS_C0_MSS_0_FIC_0_APB_MASTER_PENABLE;
wire   [31:0] MSS_C0_MSS_0_FIC_0_APB_MASTER_PRDATA;
wire          MSS_C0_MSS_0_FIC_0_APB_MASTER_PREADY;
wire          MSS_C0_MSS_0_FIC_0_APB_MASTER_PSELx;
wire          MSS_C0_MSS_0_FIC_0_APB_MASTER_PSLVERR;
wire   [31:0] MSS_C0_MSS_0_FIC_0_APB_MASTER_PWDATA;
wire          MSS_C0_MSS_0_FIC_0_APB_MASTER_PWRITE;
wire          MSS_C0_MSS_0_FIC_2_APB_M_PRESET_N;
wire          MSS_C0_MSS_0_MSS_RESET_N_M2F;
wire          OR3_0_Y;
wire          OR3_1_Y;
wire          OR3_2_Y;
wire          OR3_3_Y;
wire          OR3_4_Y;
wire          OR3_5_Y;
wire          OSC_C0_0_RCOSC_25_50MHZ_CCC_OUT_RCOSC_25_50MHZ_CCC;
wire          OSC_C0_0_RCOSC_25_50MHZ_O2F;
wire   [0:0]  RTC_SPI_CS_net_0;
wire          RTC_SPI_MISO;
wire          RTC_SPI_MOSI_net_0;
wire          RTC_SPI_SCK_net_0;
wire          SPI_0_CLK;
wire          SPI_0_DI;
wire          SPI_0_DO_net_0;
wire          SPI_0_SS0;
wire          SYSRESET_0_POWER_ON_RESET_N;
wire          SPI_0_DO_net_1;
wire          MMUART_0_TXD_M2F_net_1;
wire          GPIO_0_M2F_net_1;
wire          GPIO_1_M2F_net_1;
wire          GPIO_3_M2F_net_1;
wire          GPIO_5_M2F_net_1;
wire          GPIO_6_M2F_net_1;
wire          GPIO_7_M2F_net_1;
wire          CAN_TX_M2F_net_1;
wire          RTC_SPI_CS_net_1;
wire          RTC_SPI_SCK_net_1;
wire          RTC_SPI_MOSI_net_1;
wire          ADCS_SPI_CS_net_1;
wire          ADCS_SPI_SCK_net_1;
wire          ADCS_SPI_MOSI_net_1;
wire          GPIO_9_M2F_net_1;
wire          GPIO_8_M2F_net_1;
wire          MRAM1_CS_net_1;
wire          MRAM1_MOSI_net_1;
wire          MRAM1_SCK_net_1;
wire          MRAM1_WP_net_1;
wire          MRAM1_HOLDn_net_1;
wire          FLASH1_SPI_CS_net_1;
wire          FLASH1_SPI_MOSI_net_1;
wire          FLASH1_SPI_SCK_net_1;
wire          FLASH1_WP_net_1;
wire          FLASH1_HOLDn_net_1;
wire          MRAM2_SPI_CS_net_1;
wire          MRAM2_SPI_MOSI_net_1;
wire          MRAM2_SPI_SCK_net_1;
wire          MRAM2_WP_net_1;
wire          MRAM2_HOLDn_net_1;
wire          FLASH2_CS_net_1;
wire          FLASH2_MOSI_net_1;
wire          FLASH2_SCK_net_1;
wire          FLASH2_WP_net_1;
wire          FLASH2_HOLDn_net_1;
wire   [1:1]  SPISS_slice_0;
wire   [2:2]  SPISS_slice_1;
wire   [3:3]  SPISS_slice_2;
wire   [4:4]  SPISS_slice_3;
wire   [5:5]  SPISS_slice_4;
wire   [6:6]  SPISS_slice_5;
wire   [7:7]  SPISS_slice_6;
wire   [1:1]  SPISS_slice_7;
wire   [2:2]  SPISS_slice_8;
wire   [3:3]  SPISS_slice_9;
wire   [4:4]  SPISS_slice_10;
wire   [5:5]  SPISS_slice_11;
wire   [6:6]  SPISS_slice_12;
wire   [7:7]  SPISS_slice_13;
wire   [1:1]  SPISS_slice_14;
wire   [2:2]  SPISS_slice_15;
wire   [3:3]  SPISS_slice_16;
wire   [4:4]  SPISS_slice_17;
wire   [5:5]  SPISS_slice_18;
wire   [6:6]  SPISS_slice_19;
wire   [7:7]  SPISS_slice_20;
wire   [1:1]  SPISS_slice_21;
wire   [2:2]  SPISS_slice_22;
wire   [3:3]  SPISS_slice_23;
wire   [4:4]  SPISS_slice_24;
wire   [5:5]  SPISS_slice_25;
wire   [6:6]  SPISS_slice_26;
wire   [7:7]  SPISS_slice_27;
wire   [1:1]  SPISS_slice_28;
wire   [2:2]  SPISS_slice_29;
wire   [3:3]  SPISS_slice_30;
wire   [4:4]  SPISS_slice_31;
wire   [5:5]  SPISS_slice_32;
wire   [6:6]  SPISS_slice_33;
wire   [7:7]  SPISS_slice_34;
wire   [1:1]  SPISS_slice_35;
wire   [2:2]  SPISS_slice_36;
wire   [3:3]  SPISS_slice_37;
wire   [4:4]  SPISS_slice_38;
wire   [5:5]  SPISS_slice_39;
wire   [6:6]  SPISS_slice_40;
wire   [7:7]  SPISS_slice_41;
wire   [7:0]  SPISS_net_0;
wire   [7:0]  SPISS_net_1;
wire   [7:0]  SPISS_net_2;
wire   [7:0]  SPISS_net_3;
wire   [7:0]  SPISS_net_4;
wire   [7:0]  SPISS_net_5;
wire   [15:0] MSS_INT_F2M_net_0;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire          VCC_net;
wire          GND_net;
wire   [31:0] FIC_2_APB_M_PRDATA_const_net_0;
//--------------------------------------------------------------------
// Bus Interface Nets Declarations - Unequal Pin Widths
//--------------------------------------------------------------------
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_0_6to0;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_0;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_1_6to0;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_1;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_2_6to0;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_2;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_3_6to0;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_3;
wire   [31:0] CoreAPB3_C0_0_APBmslave0_PADDR;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_5_6to0;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_5;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_4_6to0;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_4;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PRDATA;
wire   [31:8] CoreAPB3_C0_0_APBmslave0_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_C0_0_APBmslave0_PRDATA_0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_3_7to0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_3;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_0_7to0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_1_7to0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_1;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_2_7to0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_2;
wire   [31:0] CoreAPB3_C0_0_APBmslave0_PWDATA;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_4_7to0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_4;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_5_7to0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_5;
wire   [31:8] CoreAPB3_C0_0_APBmslave1_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_C0_0_APBmslave1_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_C0_0_APBmslave1_PRDATA_0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave1_PRDATA;
wire   [31:8] CoreAPB3_C0_0_APBmslave2_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_C0_0_APBmslave2_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_C0_0_APBmslave2_PRDATA_0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave2_PRDATA;
wire   [7:0]  CoreAPB3_C0_0_APBmslave3_PRDATA;
wire   [31:8] CoreAPB3_C0_0_APBmslave3_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_C0_0_APBmslave3_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_C0_0_APBmslave3_PRDATA_0;
wire   [31:8] CoreAPB3_C0_0_APBmslave4_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_C0_0_APBmslave4_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_C0_0_APBmslave4_PRDATA_0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave4_PRDATA;
wire   [31:8] CoreAPB3_C0_0_APBmslave5_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_C0_0_APBmslave5_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_C0_0_APBmslave5_PRDATA_0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave5_PRDATA;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign VCC_net                        = 1'b1;
assign GND_net                        = 1'b0;
assign FIC_2_APB_M_PRDATA_const_net_0 = 32'h00000000;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign SPI_0_DO_net_1         = SPI_0_DO_net_0;
assign SPI_0_DO               = SPI_0_DO_net_1;
assign MMUART_0_TXD_M2F_net_1 = MMUART_0_TXD_M2F_net_0;
assign MMUART_0_TXD_M2F       = MMUART_0_TXD_M2F_net_1;
assign GPIO_0_M2F_net_1       = GPIO_0_M2F_net_0;
assign GPIO_0_M2F             = GPIO_0_M2F_net_1;
assign GPIO_1_M2F_net_1       = GPIO_1_M2F_net_0;
assign GPIO_1_M2F             = GPIO_1_M2F_net_1;
assign GPIO_3_M2F_net_1       = GPIO_3_M2F_net_0;
assign GPIO_3_M2F             = GPIO_3_M2F_net_1;
assign GPIO_5_M2F_net_1       = GPIO_5_M2F_net_0;
assign GPIO_5_M2F             = GPIO_5_M2F_net_1;
assign GPIO_6_M2F_net_1       = GPIO_6_M2F_net_0;
assign GPIO_6_M2F             = GPIO_6_M2F_net_1;
assign GPIO_7_M2F_net_1       = GPIO_7_M2F_net_0;
assign GPIO_7_M2F             = GPIO_7_M2F_net_1;
assign CAN_TX_M2F_net_1       = CAN_TX_M2F_net_0;
assign CAN_TX_M2F             = CAN_TX_M2F_net_1;
assign RTC_SPI_CS_net_1       = RTC_SPI_CS_net_0[0];
assign RTC_SPI_CS             = RTC_SPI_CS_net_1;
assign RTC_SPI_SCK_net_1      = RTC_SPI_SCK_net_0;
assign RTC_SPI_SCK            = RTC_SPI_SCK_net_1;
assign RTC_SPI_MOSI_net_1     = RTC_SPI_MOSI_net_0;
assign RTC_SPI_MOSI           = RTC_SPI_MOSI_net_1;
assign ADCS_SPI_CS_net_1      = ADCS_SPI_CS_net_0[0];
assign ADCS_SPI_CS            = ADCS_SPI_CS_net_1;
assign ADCS_SPI_SCK_net_1     = ADCS_SPI_SCK_net_0;
assign ADCS_SPI_SCK           = ADCS_SPI_SCK_net_1;
assign ADCS_SPI_MOSI_net_1    = ADCS_SPI_MOSI_net_0;
assign ADCS_SPI_MOSI          = ADCS_SPI_MOSI_net_1;
assign GPIO_9_M2F_net_1       = GPIO_9_M2F_net_0;
assign GPIO_9_M2F             = GPIO_9_M2F_net_1;
assign GPIO_8_M2F_net_1       = GPIO_8_M2F_net_0;
assign GPIO_8_M2F             = GPIO_8_M2F_net_1;
assign MRAM1_CS_net_1         = MRAM1_CS_net_0[0];
assign MRAM1_CS               = MRAM1_CS_net_1;
assign MRAM1_MOSI_net_1       = MRAM1_MOSI_net_0;
assign MRAM1_MOSI             = MRAM1_MOSI_net_1;
assign MRAM1_SCK_net_1        = MRAM1_SCK_net_0;
assign MRAM1_SCK              = MRAM1_SCK_net_1;
assign MRAM1_WP_net_1         = MRAM1_WP_net_0;
assign MRAM1_WP               = MRAM1_WP_net_1;
assign MRAM1_HOLDn_net_1      = MRAM1_HOLDn_net_0;
assign MRAM1_HOLDn            = MRAM1_HOLDn_net_1;
assign FLASH1_SPI_CS_net_1    = FLASH1_SPI_CS_net_0[0];
assign FLASH1_SPI_CS          = FLASH1_SPI_CS_net_1;
assign FLASH1_SPI_MOSI_net_1  = FLASH1_SPI_MOSI_net_0;
assign FLASH1_SPI_MOSI        = FLASH1_SPI_MOSI_net_1;
assign FLASH1_SPI_SCK_net_1   = FLASH1_SPI_SCK_net_0;
assign FLASH1_SPI_SCK         = FLASH1_SPI_SCK_net_1;
assign FLASH1_WP_net_1        = FLASH1_WP_net_0;
assign FLASH1_WP              = FLASH1_WP_net_1;
assign FLASH1_HOLDn_net_1     = FLASH1_HOLDn_net_0;
assign FLASH1_HOLDn           = FLASH1_HOLDn_net_1;
assign MRAM2_SPI_CS_net_1     = MRAM2_SPI_CS_net_0[0];
assign MRAM2_SPI_CS           = MRAM2_SPI_CS_net_1;
assign MRAM2_SPI_MOSI_net_1   = MRAM2_SPI_MOSI_net_0;
assign MRAM2_SPI_MOSI         = MRAM2_SPI_MOSI_net_1;
assign MRAM2_SPI_SCK_net_1    = MRAM2_SPI_SCK_net_0;
assign MRAM2_SPI_SCK          = MRAM2_SPI_SCK_net_1;
assign MRAM2_WP_net_1         = MRAM2_WP_net_0;
assign MRAM2_WP               = MRAM2_WP_net_1;
assign MRAM2_HOLDn_net_1      = MRAM2_HOLDn_net_0;
assign MRAM2_HOLDn            = MRAM2_HOLDn_net_1;
assign FLASH2_CS_net_1        = FLASH2_CS_net_0[0];
assign FLASH2_CS              = FLASH2_CS_net_1;
assign FLASH2_MOSI_net_1      = FLASH2_MOSI_net_0;
assign FLASH2_MOSI            = FLASH2_MOSI_net_1;
assign FLASH2_SCK_net_1       = FLASH2_SCK_net_0;
assign FLASH2_SCK             = FLASH2_SCK_net_1;
assign FLASH2_WP_net_1        = FLASH2_WP_net_0;
assign FLASH2_WP              = FLASH2_WP_net_1;
assign FLASH2_HOLDn_net_1     = FLASH2_HOLDn_net_0;
assign FLASH2_HOLDn           = FLASH2_HOLDn_net_1;
//--------------------------------------------------------------------
// Slices assignments
//--------------------------------------------------------------------
assign ADCS_SPI_CS_net_0[0]   = SPISS_net_1[0:0];
assign FLASH1_SPI_CS_net_0[0] = SPISS_net_3[0:0];
assign FLASH2_CS_net_0[0]     = SPISS_net_5[0:0];
assign MRAM1_CS_net_0[0]      = SPISS_net_2[0:0];
assign MRAM2_SPI_CS_net_0[0]  = SPISS_net_4[0:0];
assign RTC_SPI_CS_net_0[0]    = SPISS_net_0[0:0];
assign SPISS_slice_0[1]       = SPISS_net_0[1:1];
assign SPISS_slice_1[2]       = SPISS_net_0[2:2];
assign SPISS_slice_2[3]       = SPISS_net_0[3:3];
assign SPISS_slice_3[4]       = SPISS_net_0[4:4];
assign SPISS_slice_4[5]       = SPISS_net_0[5:5];
assign SPISS_slice_5[6]       = SPISS_net_0[6:6];
assign SPISS_slice_6[7]       = SPISS_net_0[7:7];
assign SPISS_slice_7[1]       = SPISS_net_1[1:1];
assign SPISS_slice_8[2]       = SPISS_net_1[2:2];
assign SPISS_slice_9[3]       = SPISS_net_1[3:3];
assign SPISS_slice_10[4]      = SPISS_net_1[4:4];
assign SPISS_slice_11[5]      = SPISS_net_1[5:5];
assign SPISS_slice_12[6]      = SPISS_net_1[6:6];
assign SPISS_slice_13[7]      = SPISS_net_1[7:7];
assign SPISS_slice_14[1]      = SPISS_net_2[1:1];
assign SPISS_slice_15[2]      = SPISS_net_2[2:2];
assign SPISS_slice_16[3]      = SPISS_net_2[3:3];
assign SPISS_slice_17[4]      = SPISS_net_2[4:4];
assign SPISS_slice_18[5]      = SPISS_net_2[5:5];
assign SPISS_slice_19[6]      = SPISS_net_2[6:6];
assign SPISS_slice_20[7]      = SPISS_net_2[7:7];
assign SPISS_slice_21[1]      = SPISS_net_3[1:1];
assign SPISS_slice_22[2]      = SPISS_net_3[2:2];
assign SPISS_slice_23[3]      = SPISS_net_3[3:3];
assign SPISS_slice_24[4]      = SPISS_net_3[4:4];
assign SPISS_slice_25[5]      = SPISS_net_3[5:5];
assign SPISS_slice_26[6]      = SPISS_net_3[6:6];
assign SPISS_slice_27[7]      = SPISS_net_3[7:7];
assign SPISS_slice_28[1]      = SPISS_net_4[1:1];
assign SPISS_slice_29[2]      = SPISS_net_4[2:2];
assign SPISS_slice_30[3]      = SPISS_net_4[3:3];
assign SPISS_slice_31[4]      = SPISS_net_4[4:4];
assign SPISS_slice_32[5]      = SPISS_net_4[5:5];
assign SPISS_slice_33[6]      = SPISS_net_4[6:6];
assign SPISS_slice_34[7]      = SPISS_net_4[7:7];
assign SPISS_slice_35[1]      = SPISS_net_5[1:1];
assign SPISS_slice_36[2]      = SPISS_net_5[2:2];
assign SPISS_slice_37[3]      = SPISS_net_5[3:3];
assign SPISS_slice_38[4]      = SPISS_net_5[4:4];
assign SPISS_slice_39[5]      = SPISS_net_5[5:5];
assign SPISS_slice_40[6]      = SPISS_net_5[6:6];
assign SPISS_slice_41[7]      = SPISS_net_5[7:7];
//--------------------------------------------------------------------
// Concatenation assignments
//--------------------------------------------------------------------
assign MSS_INT_F2M_net_0 = { 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , OR3_5_Y , OR3_4_Y , OR3_3_Y , OR3_2_Y , OR3_1_Y , OR3_0_Y };
//--------------------------------------------------------------------
// Bus Interface Nets Assignments - Unequal Pin Widths
//--------------------------------------------------------------------
assign CoreAPB3_C0_0_APBmslave0_PADDR_0_6to0 = CoreAPB3_C0_0_APBmslave0_PADDR[6:0];
assign CoreAPB3_C0_0_APBmslave0_PADDR_0 = { CoreAPB3_C0_0_APBmslave0_PADDR_0_6to0 };
assign CoreAPB3_C0_0_APBmslave0_PADDR_1_6to0 = CoreAPB3_C0_0_APBmslave0_PADDR[6:0];
assign CoreAPB3_C0_0_APBmslave0_PADDR_1 = { CoreAPB3_C0_0_APBmslave0_PADDR_1_6to0 };
assign CoreAPB3_C0_0_APBmslave0_PADDR_2_6to0 = CoreAPB3_C0_0_APBmslave0_PADDR[6:0];
assign CoreAPB3_C0_0_APBmslave0_PADDR_2 = { CoreAPB3_C0_0_APBmslave0_PADDR_2_6to0 };
assign CoreAPB3_C0_0_APBmslave0_PADDR_3_6to0 = CoreAPB3_C0_0_APBmslave0_PADDR[6:0];
assign CoreAPB3_C0_0_APBmslave0_PADDR_3 = { CoreAPB3_C0_0_APBmslave0_PADDR_3_6to0 };
assign CoreAPB3_C0_0_APBmslave0_PADDR_5_6to0 = CoreAPB3_C0_0_APBmslave0_PADDR[6:0];
assign CoreAPB3_C0_0_APBmslave0_PADDR_5 = { CoreAPB3_C0_0_APBmslave0_PADDR_5_6to0 };
assign CoreAPB3_C0_0_APBmslave0_PADDR_4_6to0 = CoreAPB3_C0_0_APBmslave0_PADDR[6:0];
assign CoreAPB3_C0_0_APBmslave0_PADDR_4 = { CoreAPB3_C0_0_APBmslave0_PADDR_4_6to0 };

assign CoreAPB3_C0_0_APBmslave0_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_C0_0_APBmslave0_PRDATA_0_7to0 = CoreAPB3_C0_0_APBmslave0_PRDATA[7:0];
assign CoreAPB3_C0_0_APBmslave0_PRDATA_0 = { CoreAPB3_C0_0_APBmslave0_PRDATA_0_31to8, CoreAPB3_C0_0_APBmslave0_PRDATA_0_7to0 };

assign CoreAPB3_C0_0_APBmslave0_PWDATA_3_7to0 = CoreAPB3_C0_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_C0_0_APBmslave0_PWDATA_3 = { CoreAPB3_C0_0_APBmslave0_PWDATA_3_7to0 };
assign CoreAPB3_C0_0_APBmslave0_PWDATA_0_7to0 = CoreAPB3_C0_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_C0_0_APBmslave0_PWDATA_0 = { CoreAPB3_C0_0_APBmslave0_PWDATA_0_7to0 };
assign CoreAPB3_C0_0_APBmslave0_PWDATA_1_7to0 = CoreAPB3_C0_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_C0_0_APBmslave0_PWDATA_1 = { CoreAPB3_C0_0_APBmslave0_PWDATA_1_7to0 };
assign CoreAPB3_C0_0_APBmslave0_PWDATA_2_7to0 = CoreAPB3_C0_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_C0_0_APBmslave0_PWDATA_2 = { CoreAPB3_C0_0_APBmslave0_PWDATA_2_7to0 };
assign CoreAPB3_C0_0_APBmslave0_PWDATA_4_7to0 = CoreAPB3_C0_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_C0_0_APBmslave0_PWDATA_4 = { CoreAPB3_C0_0_APBmslave0_PWDATA_4_7to0 };
assign CoreAPB3_C0_0_APBmslave0_PWDATA_5_7to0 = CoreAPB3_C0_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_C0_0_APBmslave0_PWDATA_5 = { CoreAPB3_C0_0_APBmslave0_PWDATA_5_7to0 };

assign CoreAPB3_C0_0_APBmslave1_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_C0_0_APBmslave1_PRDATA_0_7to0 = CoreAPB3_C0_0_APBmslave1_PRDATA[7:0];
assign CoreAPB3_C0_0_APBmslave1_PRDATA_0 = { CoreAPB3_C0_0_APBmslave1_PRDATA_0_31to8, CoreAPB3_C0_0_APBmslave1_PRDATA_0_7to0 };

assign CoreAPB3_C0_0_APBmslave2_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_C0_0_APBmslave2_PRDATA_0_7to0 = CoreAPB3_C0_0_APBmslave2_PRDATA[7:0];
assign CoreAPB3_C0_0_APBmslave2_PRDATA_0 = { CoreAPB3_C0_0_APBmslave2_PRDATA_0_31to8, CoreAPB3_C0_0_APBmslave2_PRDATA_0_7to0 };

assign CoreAPB3_C0_0_APBmslave3_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_C0_0_APBmslave3_PRDATA_0_7to0 = CoreAPB3_C0_0_APBmslave3_PRDATA[7:0];
assign CoreAPB3_C0_0_APBmslave3_PRDATA_0 = { CoreAPB3_C0_0_APBmslave3_PRDATA_0_31to8, CoreAPB3_C0_0_APBmslave3_PRDATA_0_7to0 };

assign CoreAPB3_C0_0_APBmslave4_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_C0_0_APBmslave4_PRDATA_0_7to0 = CoreAPB3_C0_0_APBmslave4_PRDATA[7:0];
assign CoreAPB3_C0_0_APBmslave4_PRDATA_0 = { CoreAPB3_C0_0_APBmslave4_PRDATA_0_31to8, CoreAPB3_C0_0_APBmslave4_PRDATA_0_7to0 };

assign CoreAPB3_C0_0_APBmslave5_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_C0_0_APBmslave5_PRDATA_0_7to0 = CoreAPB3_C0_0_APBmslave5_PRDATA[7:0];
assign CoreAPB3_C0_0_APBmslave5_PRDATA_0 = { CoreAPB3_C0_0_APBmslave5_PRDATA_0_31to8, CoreAPB3_C0_0_APBmslave5_PRDATA_0_7to0 };

//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------CoreAPB3_C0
CoreAPB3_C0 CoreAPB3_C0_0(
        // Inputs
        .PSEL      ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PSELx ),
        .PENABLE   ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PENABLE ),
        .PWRITE    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PWRITE ),
        .PREADYS0  ( CoreAPB3_C0_0_APBmslave0_PREADY ),
        .PSLVERRS0 ( CoreAPB3_C0_0_APBmslave0_PSLVERR ),
        .PREADYS1  ( CoreAPB3_C0_0_APBmslave1_PREADY ),
        .PSLVERRS1 ( CoreAPB3_C0_0_APBmslave1_PSLVERR ),
        .PREADYS2  ( CoreAPB3_C0_0_APBmslave2_PREADY ),
        .PSLVERRS2 ( CoreAPB3_C0_0_APBmslave2_PSLVERR ),
        .PREADYS3  ( CoreAPB3_C0_0_APBmslave3_PREADY ),
        .PSLVERRS3 ( CoreAPB3_C0_0_APBmslave3_PSLVERR ),
        .PREADYS4  ( CoreAPB3_C0_0_APBmslave4_PREADY ),
        .PSLVERRS4 ( CoreAPB3_C0_0_APBmslave4_PSLVERR ),
        .PREADYS5  ( CoreAPB3_C0_0_APBmslave5_PREADY ),
        .PSLVERRS5 ( CoreAPB3_C0_0_APBmslave5_PSLVERR ),
        .PADDR     ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PADDR ),
        .PWDATA    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PWDATA ),
        .PRDATAS0  ( CoreAPB3_C0_0_APBmslave0_PRDATA_0 ),
        .PRDATAS1  ( CoreAPB3_C0_0_APBmslave1_PRDATA_0 ),
        .PRDATAS2  ( CoreAPB3_C0_0_APBmslave2_PRDATA_0 ),
        .PRDATAS3  ( CoreAPB3_C0_0_APBmslave3_PRDATA_0 ),
        .PRDATAS4  ( CoreAPB3_C0_0_APBmslave4_PRDATA_0 ),
        .PRDATAS5  ( CoreAPB3_C0_0_APBmslave5_PRDATA_0 ),
        // Outputs
        .PREADY    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PREADY ),
        .PSLVERR   ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PSLVERR ),
        .PSELS0    ( CoreAPB3_C0_0_APBmslave0_PSELx ),
        .PENABLES  ( CoreAPB3_C0_0_APBmslave0_PENABLE ),
        .PWRITES   ( CoreAPB3_C0_0_APBmslave0_PWRITE ),
        .PSELS1    ( CoreAPB3_C0_0_APBmslave1_PSELx ),
        .PSELS2    ( CoreAPB3_C0_0_APBmslave2_PSELx ),
        .PSELS3    ( CoreAPB3_C0_0_APBmslave3_PSELx ),
        .PSELS4    ( CoreAPB3_C0_0_APBmslave4_PSELx ),
        .PSELS5    ( CoreAPB3_C0_0_APBmslave5_PSELx ),
        .PRDATA    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PRDATA ),
        .PADDRS    ( CoreAPB3_C0_0_APBmslave0_PADDR ),
        .PWDATAS   ( CoreAPB3_C0_0_APBmslave0_PWDATA ) 
        );

//--------CoreResetP_C0
CoreResetP_C0 CoreResetP_C0_0(
        // Inputs
        .RESET_N_M2F          ( MSS_C0_MSS_0_MSS_RESET_N_M2F ),
        .FIC_2_APB_M_PRESET_N ( MSS_C0_MSS_0_FIC_2_APB_M_PRESET_N ),
        .POWER_ON_RESET_N     ( SYSRESET_0_POWER_ON_RESET_N ),
        .FAB_RESET_N          ( VCC_net ),
        .RCOSC_25_50MHZ       ( OSC_C0_0_RCOSC_25_50MHZ_O2F ),
        .CLK_BASE             ( FCCC_C0_0_GL0 ),
        .FPLL_LOCK            ( VCC_net ),
        .CONFIG1_DONE         ( VCC_net ),
        .CONFIG2_DONE         ( VCC_net ),
        // Outputs
        .MSS_HPMS_READY       ( CoreResetP_C0_0_MSS_HPMS_READY ),
        .DDR_READY            (  ),
        .RESET_N_F2M          ( CoreResetP_C0_0_RESET_N_F2M ),
        .M3_RESET_N           ( CoreResetP_C0_0_M3_RESET_N ),
        .FDDR_CORE_RESET_N    (  ),
        .INIT_DONE            (  ) 
        );

//--------CORESPI_C0
CORESPI_C0 CORESPI_C0_0(
        // Inputs
        .PCLK       ( FCCC_C0_0_GL0 ),
        .PRESETN    ( CoreResetP_C0_0_MSS_HPMS_READY ),
        .SPISSI     ( GND_net ),
        .SPISDI     ( RTC_SPI_MISO ),
        .SPICLKI    ( GND_net ),
        .PSEL       ( CoreAPB3_C0_0_APBmslave0_PSELx ),
        .PENABLE    ( CoreAPB3_C0_0_APBmslave0_PENABLE ),
        .PWRITE     ( CoreAPB3_C0_0_APBmslave0_PWRITE ),
        .PADDR      ( CoreAPB3_C0_0_APBmslave0_PADDR_0 ),
        .PWDATA     ( CoreAPB3_C0_0_APBmslave0_PWDATA_0 ),
        // Outputs
        .SPIINT     ( CORESPI_C0_0_SPIINT ),
        .SPIRXAVAIL ( CORESPI_C0_0_SPIRXAVAIL ),
        .SPITXRFM   ( CORESPI_C0_0_SPITXRFM ),
        .SPISCLKO   ( RTC_SPI_SCK_net_0 ),
        .SPIOEN     (  ),
        .SPISDO     ( RTC_SPI_MOSI_net_0 ),
        .SPIMODE    (  ),
        .PREADY     ( CoreAPB3_C0_0_APBmslave0_PREADY ),
        .PSLVERR    ( CoreAPB3_C0_0_APBmslave0_PSLVERR ),
        .SPISS      ( SPISS_net_0 ),
        .PRDATA     ( CoreAPB3_C0_0_APBmslave0_PRDATA ) 
        );

//--------CORESPI_C1
CORESPI_C1 CORESPI_C1_0(
        // Inputs
        .PCLK       ( FCCC_C0_0_GL0 ),
        .PRESETN    ( CoreResetP_C0_0_MSS_HPMS_READY ),
        .SPISSI     ( GND_net ),
        .SPISDI     ( ADCS_SPI_MISO ),
        .SPICLKI    ( GND_net ),
        .PSEL       ( CoreAPB3_C0_0_APBmslave1_PSELx ),
        .PENABLE    ( CoreAPB3_C0_0_APBmslave0_PENABLE ),
        .PWRITE     ( CoreAPB3_C0_0_APBmslave0_PWRITE ),
        .PADDR      ( CoreAPB3_C0_0_APBmslave0_PADDR_1 ),
        .PWDATA     ( CoreAPB3_C0_0_APBmslave0_PWDATA_1 ),
        // Outputs
        .SPIINT     ( CORESPI_C1_0_SPIINT ),
        .SPIRXAVAIL ( CORESPI_C1_0_SPIRXAVAIL ),
        .SPITXRFM   ( CORESPI_C1_0_SPITXRFM ),
        .SPISCLKO   ( ADCS_SPI_SCK_net_0 ),
        .SPIOEN     (  ),
        .SPISDO     ( ADCS_SPI_MOSI_net_0 ),
        .SPIMODE    (  ),
        .PREADY     ( CoreAPB3_C0_0_APBmslave1_PREADY ),
        .PSLVERR    ( CoreAPB3_C0_0_APBmslave1_PSLVERR ),
        .SPISS      ( SPISS_net_1 ),
        .PRDATA     ( CoreAPB3_C0_0_APBmslave1_PRDATA ) 
        );

//--------CORESPI_C1
CORESPI_C1 CORESPI_C1_1(
        // Inputs
        .PCLK       ( FCCC_C0_0_GL0 ),
        .PRESETN    ( CoreResetP_C0_0_MSS_HPMS_READY ),
        .SPISSI     ( GND_net ),
        .SPISDI     ( MRAM1_MISO ),
        .SPICLKI    ( GND_net ),
        .PSEL       ( CoreAPB3_C0_0_APBmslave2_PSELx ),
        .PENABLE    ( CoreAPB3_C0_0_APBmslave0_PENABLE ),
        .PWRITE     ( CoreAPB3_C0_0_APBmslave0_PWRITE ),
        .PADDR      ( CoreAPB3_C0_0_APBmslave0_PADDR_2 ),
        .PWDATA     ( CoreAPB3_C0_0_APBmslave0_PWDATA_2 ),
        // Outputs
        .SPIINT     ( CORESPI_C1_1_SPIINT ),
        .SPIRXAVAIL ( CORESPI_C1_1_SPIRXAVAIL ),
        .SPITXRFM   ( CORESPI_C1_1_SPITXRFM ),
        .SPISCLKO   ( MRAM1_SCK_net_0 ),
        .SPIOEN     (  ),
        .SPISDO     ( MRAM1_MOSI_net_0 ),
        .SPIMODE    (  ),
        .PREADY     ( CoreAPB3_C0_0_APBmslave2_PREADY ),
        .PSLVERR    ( CoreAPB3_C0_0_APBmslave2_PSLVERR ),
        .SPISS      ( SPISS_net_2 ),
        .PRDATA     ( CoreAPB3_C0_0_APBmslave2_PRDATA ) 
        );

//--------CORESPI_C1
CORESPI_C1 CORESPI_C1_2(
        // Inputs
        .PCLK       ( FCCC_C0_0_GL0 ),
        .PRESETN    ( CoreResetP_C0_0_MSS_HPMS_READY ),
        .SPISSI     ( GND_net ),
        .SPISDI     ( FLASH1_SPI_MISO ),
        .SPICLKI    ( GND_net ),
        .PSEL       ( CoreAPB3_C0_0_APBmslave3_PSELx ),
        .PENABLE    ( CoreAPB3_C0_0_APBmslave0_PENABLE ),
        .PWRITE     ( CoreAPB3_C0_0_APBmslave0_PWRITE ),
        .PADDR      ( CoreAPB3_C0_0_APBmslave0_PADDR_3 ),
        .PWDATA     ( CoreAPB3_C0_0_APBmslave0_PWDATA_3 ),
        // Outputs
        .SPIINT     ( CORESPI_C1_2_SPIINT ),
        .SPIRXAVAIL ( CORESPI_C1_2_SPIRXAVAIL ),
        .SPITXRFM   ( CORESPI_C1_2_SPITXRFM ),
        .SPISCLKO   ( FLASH1_SPI_SCK_net_0 ),
        .SPIOEN     (  ),
        .SPISDO     ( FLASH1_SPI_MOSI_net_0 ),
        .SPIMODE    (  ),
        .PREADY     ( CoreAPB3_C0_0_APBmslave3_PREADY ),
        .PSLVERR    ( CoreAPB3_C0_0_APBmslave3_PSLVERR ),
        .SPISS      ( SPISS_net_3 ),
        .PRDATA     ( CoreAPB3_C0_0_APBmslave3_PRDATA ) 
        );

//--------CORESPI_C1
CORESPI_C1 CORESPI_C1_3(
        // Inputs
        .PCLK       ( FCCC_C0_0_GL0 ),
        .PRESETN    ( CoreResetP_C0_0_MSS_HPMS_READY ),
        .SPISSI     ( GND_net ),
        .SPISDI     ( MRAM2_SPI_MISO ),
        .SPICLKI    ( GND_net ),
        .PSEL       ( CoreAPB3_C0_0_APBmslave4_PSELx ),
        .PENABLE    ( CoreAPB3_C0_0_APBmslave0_PENABLE ),
        .PWRITE     ( CoreAPB3_C0_0_APBmslave0_PWRITE ),
        .PADDR      ( CoreAPB3_C0_0_APBmslave0_PADDR_4 ),
        .PWDATA     ( CoreAPB3_C0_0_APBmslave0_PWDATA_4 ),
        // Outputs
        .SPIINT     ( CORESPI_C1_3_SPIINT ),
        .SPIRXAVAIL ( CORESPI_C1_3_SPIRXAVAIL ),
        .SPITXRFM   ( CORESPI_C1_3_SPITXRFM ),
        .SPISCLKO   ( MRAM2_SPI_SCK_net_0 ),
        .SPIOEN     (  ),
        .SPISDO     ( MRAM2_SPI_MOSI_net_0 ),
        .SPIMODE    (  ),
        .PREADY     ( CoreAPB3_C0_0_APBmslave4_PREADY ),
        .PSLVERR    ( CoreAPB3_C0_0_APBmslave4_PSLVERR ),
        .SPISS      ( SPISS_net_4 ),
        .PRDATA     ( CoreAPB3_C0_0_APBmslave4_PRDATA ) 
        );

//--------CORESPI_C1
CORESPI_C1 CORESPI_C1_4(
        // Inputs
        .PCLK       ( FCCC_C0_0_GL0 ),
        .PRESETN    ( CoreResetP_C0_0_MSS_HPMS_READY ),
        .SPISSI     ( GND_net ),
        .SPISDI     ( FLASH2_MISO ),
        .SPICLKI    ( GND_net ),
        .PSEL       ( CoreAPB3_C0_0_APBmslave5_PSELx ),
        .PENABLE    ( CoreAPB3_C0_0_APBmslave0_PENABLE ),
        .PWRITE     ( CoreAPB3_C0_0_APBmslave0_PWRITE ),
        .PADDR      ( CoreAPB3_C0_0_APBmslave0_PADDR_5 ),
        .PWDATA     ( CoreAPB3_C0_0_APBmslave0_PWDATA_5 ),
        // Outputs
        .SPIINT     ( CORESPI_C1_4_SPIINT ),
        .SPIRXAVAIL ( CORESPI_C1_4_SPIRXAVAIL ),
        .SPITXRFM   ( CORESPI_C1_4_SPITXRFM ),
        .SPISCLKO   ( FLASH2_SCK_net_0 ),
        .SPIOEN     (  ),
        .SPISDO     ( FLASH2_MOSI_net_0 ),
        .SPIMODE    (  ),
        .PREADY     ( CoreAPB3_C0_0_APBmslave5_PREADY ),
        .PSLVERR    ( CoreAPB3_C0_0_APBmslave5_PSLVERR ),
        .SPISS      ( SPISS_net_5 ),
        .PRDATA     ( CoreAPB3_C0_0_APBmslave5_PRDATA ) 
        );

//--------FCCC_C0
FCCC_C0 FCCC_C0_0(
        // Inputs
        .RCOSC_25_50MHZ ( OSC_C0_0_RCOSC_25_50MHZ_CCC_OUT_RCOSC_25_50MHZ_CCC ),
        // Outputs
        .GL0            ( FCCC_C0_0_GL0 ),
        .LOCK           ( FCCC_C0_0_LOCK ) 
        );

//--------MSS_C0_MSS
MSS_C0_MSS MSS_C0_MSS_0(
        // Inputs
        .MCCC_CLK_BASE          ( FCCC_C0_0_GL0 ),
        .MMUART_0_RXD_F2M       ( MMUART_0_RXD_F2M ),
        .SPI_0_DI               ( SPI_0_DI ),
        .CAN_RX_F2M             ( CAN_RX_F2M ),
        .MCCC_CLK_BASE_PLL_LOCK ( FCCC_C0_0_LOCK ),
        .MSS_RESET_N_F2M        ( CoreResetP_C0_0_RESET_N_F2M ),
        .FIC_0_APB_M_PREADY     ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PREADY ),
        .FIC_0_APB_M_PSLVERR    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PSLVERR ),
        .FIC_2_APB_M_PREADY     ( VCC_net ), // tied to 1'b1 from definition
        .FIC_2_APB_M_PSLVERR    ( GND_net ), // tied to 1'b0 from definition
        .M3_RESET_N             ( CoreResetP_C0_0_M3_RESET_N ),
        .MSS_INT_F2M            ( MSS_INT_F2M_net_0 ),
        .FIC_0_APB_M_PRDATA     ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PRDATA ),
        .FIC_2_APB_M_PRDATA     ( FIC_2_APB_M_PRDATA_const_net_0 ), // tied to 32'h00000000 from definition
        // Outputs
        .MMUART_0_TXD_M2F       ( MMUART_0_TXD_M2F_net_0 ),
        .SPI_0_DO               ( SPI_0_DO_net_0 ),
        .GPIO_0_M2F             ( GPIO_0_M2F_net_0 ),
        .GPIO_1_M2F             ( GPIO_1_M2F_net_0 ),
        .GPIO_3_M2F             ( GPIO_3_M2F_net_0 ),
        .GPIO_5_M2F             ( GPIO_5_M2F_net_0 ),
        .CAN_TX_M2F             ( CAN_TX_M2F_net_0 ),
        .CAN_TX_EN_N_M2F        (  ),
        .GPIO_6_M2F             ( GPIO_6_M2F_net_0 ),
        .GPIO_7_M2F             ( GPIO_7_M2F_net_0 ),
        .MSS_RESET_N_M2F        ( MSS_C0_MSS_0_MSS_RESET_N_M2F ),
        .FIC_0_APB_M_PSEL       ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PSELx ),
        .FIC_0_APB_M_PWRITE     ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PWRITE ),
        .FIC_0_APB_M_PENABLE    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PENABLE ),
        .FIC_2_APB_M_PRESET_N   ( MSS_C0_MSS_0_FIC_2_APB_M_PRESET_N ),
        .FIC_2_APB_M_PCLK       (  ),
        .FIC_2_APB_M_PWRITE     (  ),
        .FIC_2_APB_M_PENABLE    (  ),
        .FIC_2_APB_M_PSEL       (  ),
        .GPIO_8_M2F             ( GPIO_8_M2F_net_0 ),
        .GPIO_9_M2F             ( GPIO_9_M2F_net_0 ),
        .GPIO_10_M2F            ( MRAM1_WP_net_0 ),
        .GPIO_11_M2F            ( MRAM1_HOLDn_net_0 ),
        .GPIO_12_M2F            ( FLASH1_WP_net_0 ),
        .GPIO_13_M2F            ( FLASH1_HOLDn_net_0 ),
        .GPIO_14_M2F            ( MRAM2_WP_net_0 ),
        .GPIO_15_M2F            ( MRAM2_HOLDn_net_0 ),
        .FIC_0_APB_M_PADDR      ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PADDR ),
        .FIC_0_APB_M_PWDATA     ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PWDATA ),
        .FIC_2_APB_M_PADDR      (  ),
        .FIC_2_APB_M_PWDATA     (  ),
        .GPIO_16_M2F            ( FLASH2_WP_net_0 ),
        .GPIO_17_M2F            ( FLASH2_HOLDn_net_0 ),
        // Inouts
        .SPI_0_CLK              ( SPI_0_CLK ),
        .SPI_0_SS0              ( SPI_0_SS0 ) 
        );

//--------OR3
OR3 OR3_0(
        // Inputs
        .A ( CORESPI_C0_0_SPIINT ),
        .B ( CORESPI_C0_0_SPIRXAVAIL ),
        .C ( CORESPI_C0_0_SPITXRFM ),
        // Outputs
        .Y ( OR3_0_Y ) 
        );

//--------OR3
OR3 OR3_1(
        // Inputs
        .A ( CORESPI_C1_0_SPIINT ),
        .B ( CORESPI_C1_0_SPIRXAVAIL ),
        .C ( CORESPI_C1_0_SPITXRFM ),
        // Outputs
        .Y ( OR3_1_Y ) 
        );

//--------OR3
OR3 OR3_2(
        // Inputs
        .A ( CORESPI_C1_1_SPIINT ),
        .B ( CORESPI_C1_1_SPIRXAVAIL ),
        .C ( CORESPI_C1_1_SPITXRFM ),
        // Outputs
        .Y ( OR3_2_Y ) 
        );

//--------OR3
OR3 OR3_3(
        // Inputs
        .A ( CORESPI_C1_2_SPIINT ),
        .B ( CORESPI_C1_2_SPIRXAVAIL ),
        .C ( CORESPI_C1_2_SPITXRFM ),
        // Outputs
        .Y ( OR3_3_Y ) 
        );

//--------OR3
OR3 OR3_4(
        // Inputs
        .A ( CORESPI_C1_3_SPIINT ),
        .B ( CORESPI_C1_3_SPIRXAVAIL ),
        .C ( CORESPI_C1_3_SPITXRFM ),
        // Outputs
        .Y ( OR3_4_Y ) 
        );

//--------OR3
OR3 OR3_5(
        // Inputs
        .A ( CORESPI_C1_4_SPIINT ),
        .B ( CORESPI_C1_4_SPIRXAVAIL ),
        .C ( CORESPI_C1_4_SPITXRFM ),
        // Outputs
        .Y ( OR3_5_Y ) 
        );

//--------OSC_C0
OSC_C0 OSC_C0_0(
        // Outputs
        .RCOSC_25_50MHZ_O2F ( OSC_C0_0_RCOSC_25_50MHZ_O2F ),
        .RCOSC_25_50MHZ_CCC ( OSC_C0_0_RCOSC_25_50MHZ_CCC_OUT_RCOSC_25_50MHZ_CCC ) 
        );

//--------SYSRESET
SYSRESET SYSRESET_0(
        // Inputs
        .DEVRST_N         ( DEVRST_N ),
        // Outputs
        .POWER_ON_RESET_N ( SYSRESET_0_POWER_ON_RESET_N ) 
        );


endmodule
