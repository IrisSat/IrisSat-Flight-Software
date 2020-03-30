//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Mon Mar 30 00:06:52 2020
// Version: v12.1 12.600.0.14
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// cdh_tsat5_system_sb
module cdh_tsat5_system_sb(
    // Inputs
    CAN_RX_F2M,
    DEVRST_N,
    FAB_RESET_N,
    GPIO_Input,
    MMUART_0_RXD_F2M,
    SPISDI,
    m_miso,
    // Outputs
    CAN_TX_EN_N_M2F,
    CAN_TX_M2F,
    FAB_CCC_GL0,
    FAB_CCC_LOCK,
    GPIO_0_M2F,
    GPIO_10_M2F,
    GPIO_11_M2F,
    GPIO_12_M2F,
    GPIO_1_M2F,
    GPIO_3_M2F,
    GPIO_5_M2F,
    GPIO_7_M2F,
    GPIO_8_M2F,
    GPIO_9_M2F,
    INIT_DONE,
    MMUART_0_TXD_M2F,
    MSS_READY,
    POWER_ON_RESET_N,
    SPISCLKO,
    SPISDO,
    SPISS,
    enable_master,
    m_mosi,
    m_sck,
    m_ss
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input        CAN_RX_F2M;
input        DEVRST_N;
input        FAB_RESET_N;
input        GPIO_Input;
input        MMUART_0_RXD_F2M;
input        SPISDI;
input        m_miso;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output       CAN_TX_EN_N_M2F;
output       CAN_TX_M2F;
output       FAB_CCC_GL0;
output       FAB_CCC_LOCK;
output       GPIO_0_M2F;
output       GPIO_10_M2F;
output       GPIO_11_M2F;
output       GPIO_12_M2F;
output       GPIO_1_M2F;
output       GPIO_3_M2F;
output       GPIO_5_M2F;
output       GPIO_7_M2F;
output       GPIO_8_M2F;
output       GPIO_9_M2F;
output       INIT_DONE;
output       MMUART_0_TXD_M2F;
output       MSS_READY;
output       POWER_ON_RESET_N;
output       SPISCLKO;
output       SPISDO;
output [7:0] SPISS;
output       enable_master;
output       m_mosi;
output       m_sck;
output [7:0] m_ss;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire          CAN_RX_F2M;
wire          CAN_TX_EN_N_M2F_net_0;
wire          CAN_TX_M2F_net_0;
wire   [31:0] cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PADDR;
wire          cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PENABLE;
wire   [31:0] cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PRDATA;
wire          cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PREADY;
wire          cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PSELx;
wire          cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PSLVERR;
wire   [31:0] cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PWDATA;
wire          cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PWRITE;
wire          cdh_tsat5_system_sb_MSS_TMP_0_FIC_2_APB_M_PRESET_N;
wire          cdh_tsat5_system_sb_MSS_TMP_0_MSS_RESET_N_M2F;
wire          CoreAPB3_0_APBmslave0_PENABLE;
wire          CoreAPB3_0_APBmslave0_PREADY;
wire          CoreAPB3_0_APBmslave0_PSELx;
wire          CoreAPB3_0_APBmslave0_PSLVERR;
wire          CoreAPB3_0_APBmslave0_PWRITE;
wire          CoreAPB3_0_APBmslave1_PREADY;
wire          CoreAPB3_0_APBmslave1_PSELx;
wire          CoreAPB3_0_APBmslave1_PSLVERR;
wire          CORERESETP_0_RESET_N_F2M;
wire          CORESPI1_1_0_SPIINT;
wire          CORESPI1_1_0_SPIRXAVAIL;
wire          CORESPI1_1_0_SPITXRFM;
wire          CORESPI_0_0_intr_or_0_Y;
wire          CORESPI_0_0_SPIINT;
wire          CORESPI_0_0_SPIRXAVAIL;
wire          CORESPI_0_0_SPITXRFM;
wire          DEVRST_N;
wire          enable_master_net_0;
wire          FAB_CCC_GL0_net_0;
wire          FAB_CCC_LOCK_net_0;
wire          FAB_RESET_N;
wire          FABOSC_0_RCOSC_25_50MHZ_CCC_OUT_RCOSC_25_50MHZ_CCC;
wire          FABOSC_0_RCOSC_25_50MHZ_O2F;
wire          GPIO_0_M2F_net_0;
wire          GPIO_1_M2F_net_0;
wire          GPIO_3_M2F_net_0;
wire          GPIO_5_M2F_net_0;
wire          GPIO_7_M2F_net_0;
wire          GPIO_8_M2F_net_0;
wire          GPIO_9_M2F_net_0;
wire          GPIO_10_M2F_net_0;
wire          GPIO_11_M2F_net_0;
wire          GPIO_12_M2F_net_0;
wire          GPIO_Input;
wire          INIT_DONE_net_0;
wire          m_miso;
wire          m_mosi_net_0;
wire          m_sck_net_0;
wire   [7:0]  m_ss_net_0;
wire          MMUART_0_RXD_F2M;
wire          MMUART_0_TXD_M2F_net_0;
wire          MSS_READY_net_0;
wire          OR3_0_Y;
wire          POWER_ON_RESET_N_net_0;
wire          SPISCLKO_net_0;
wire          SPISDI;
wire          SPISDO_net_0;
wire   [7:0]  SPISS_net_0;
wire          POWER_ON_RESET_N_net_1;
wire          INIT_DONE_net_1;
wire          FAB_CCC_GL0_net_1;
wire          FAB_CCC_LOCK_net_1;
wire          MSS_READY_net_1;
wire          MMUART_0_TXD_M2F_net_1;
wire          CAN_TX_M2F_net_1;
wire          CAN_TX_EN_N_M2F_net_1;
wire          GPIO_0_M2F_net_1;
wire          GPIO_1_M2F_net_1;
wire          GPIO_3_M2F_net_1;
wire          GPIO_5_M2F_net_1;
wire          GPIO_7_M2F_net_1;
wire          GPIO_8_M2F_net_1;
wire          GPIO_9_M2F_net_1;
wire          GPIO_10_M2F_net_1;
wire          GPIO_11_M2F_net_1;
wire          GPIO_12_M2F_net_1;
wire          enable_master_net_1;
wire          m_mosi_net_1;
wire          m_sck_net_1;
wire   [7:0]  m_ss_net_1;
wire          SPISDO_net_1;
wire          SPISCLKO_net_1;
wire   [7:0]  SPISS_net_1;
wire   [15:0] MSS_INT_F2M_net_0;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire          GND_net;
wire          VCC_net;
wire   [7:2]  PADDR_const_net_0;
wire   [7:0]  PWDATA_const_net_0;
wire   [31:0] IADDR_const_net_0;
wire   [31:0] SDIF0_PRDATA_const_net_0;
wire   [31:0] SDIF1_PRDATA_const_net_0;
wire   [31:0] SDIF2_PRDATA_const_net_0;
wire   [31:0] SDIF3_PRDATA_const_net_0;
wire   [31:0] FIC_2_APB_M_PRDATA_const_net_0;
wire   [31:0] PRDATAS2_const_net_0;
wire   [31:0] PRDATAS3_const_net_0;
wire   [31:0] PRDATAS4_const_net_0;
wire   [31:0] PRDATAS5_const_net_0;
wire   [31:0] PRDATAS6_const_net_0;
wire   [31:0] PRDATAS7_const_net_0;
wire   [31:0] PRDATAS8_const_net_0;
wire   [31:0] PRDATAS9_const_net_0;
wire   [31:0] PRDATAS10_const_net_0;
wire   [31:0] PRDATAS11_const_net_0;
wire   [31:0] PRDATAS12_const_net_0;
wire   [31:0] PRDATAS13_const_net_0;
wire   [31:0] PRDATAS14_const_net_0;
wire   [31:0] PRDATAS15_const_net_0;
wire   [31:0] PRDATAS16_const_net_0;
//--------------------------------------------------------------------
// Bus Interface Nets Declarations - Unequal Pin Widths
//--------------------------------------------------------------------
wire   [6:0]  CoreAPB3_0_APBmslave0_PADDR_0_6to0;
wire   [6:0]  CoreAPB3_0_APBmslave0_PADDR_0;
wire   [31:0] CoreAPB3_0_APBmslave0_PADDR;
wire   [6:0]  CoreAPB3_0_APBmslave0_PADDR_1_6to0;
wire   [6:0]  CoreAPB3_0_APBmslave0_PADDR_1;
wire   [7:0]  CoreAPB3_0_APBmslave0_PRDATA;
wire   [31:8] CoreAPB3_0_APBmslave0_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_0_APBmslave0_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_0_APBmslave0_PRDATA_0;
wire   [7:0]  CoreAPB3_0_APBmslave0_PWDATA_0_7to0;
wire   [7:0]  CoreAPB3_0_APBmslave0_PWDATA_0;
wire   [31:0] CoreAPB3_0_APBmslave0_PWDATA;
wire   [7:0]  CoreAPB3_0_APBmslave0_PWDATA_1_7to0;
wire   [7:0]  CoreAPB3_0_APBmslave0_PWDATA_1;
wire   [31:8] CoreAPB3_0_APBmslave1_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_0_APBmslave1_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_0_APBmslave1_PRDATA_0;
wire   [7:0]  CoreAPB3_0_APBmslave1_PRDATA;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign GND_net                        = 1'b0;
assign VCC_net                        = 1'b1;
assign PADDR_const_net_0              = 6'h00;
assign PWDATA_const_net_0             = 8'h00;
assign IADDR_const_net_0              = 32'h00000000;
assign SDIF0_PRDATA_const_net_0       = 32'h00000000;
assign SDIF1_PRDATA_const_net_0       = 32'h00000000;
assign SDIF2_PRDATA_const_net_0       = 32'h00000000;
assign SDIF3_PRDATA_const_net_0       = 32'h00000000;
assign FIC_2_APB_M_PRDATA_const_net_0 = 32'h00000000;
assign PRDATAS2_const_net_0           = 32'h00000000;
assign PRDATAS3_const_net_0           = 32'h00000000;
assign PRDATAS4_const_net_0           = 32'h00000000;
assign PRDATAS5_const_net_0           = 32'h00000000;
assign PRDATAS6_const_net_0           = 32'h00000000;
assign PRDATAS7_const_net_0           = 32'h00000000;
assign PRDATAS8_const_net_0           = 32'h00000000;
assign PRDATAS9_const_net_0           = 32'h00000000;
assign PRDATAS10_const_net_0          = 32'h00000000;
assign PRDATAS11_const_net_0          = 32'h00000000;
assign PRDATAS12_const_net_0          = 32'h00000000;
assign PRDATAS13_const_net_0          = 32'h00000000;
assign PRDATAS14_const_net_0          = 32'h00000000;
assign PRDATAS15_const_net_0          = 32'h00000000;
assign PRDATAS16_const_net_0          = 32'h00000000;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign POWER_ON_RESET_N_net_1 = POWER_ON_RESET_N_net_0;
assign POWER_ON_RESET_N       = POWER_ON_RESET_N_net_1;
assign INIT_DONE_net_1        = INIT_DONE_net_0;
assign INIT_DONE              = INIT_DONE_net_1;
assign FAB_CCC_GL0_net_1      = FAB_CCC_GL0_net_0;
assign FAB_CCC_GL0            = FAB_CCC_GL0_net_1;
assign FAB_CCC_LOCK_net_1     = FAB_CCC_LOCK_net_0;
assign FAB_CCC_LOCK           = FAB_CCC_LOCK_net_1;
assign MSS_READY_net_1        = MSS_READY_net_0;
assign MSS_READY              = MSS_READY_net_1;
assign MMUART_0_TXD_M2F_net_1 = MMUART_0_TXD_M2F_net_0;
assign MMUART_0_TXD_M2F       = MMUART_0_TXD_M2F_net_1;
assign CAN_TX_M2F_net_1       = CAN_TX_M2F_net_0;
assign CAN_TX_M2F             = CAN_TX_M2F_net_1;
assign CAN_TX_EN_N_M2F_net_1  = CAN_TX_EN_N_M2F_net_0;
assign CAN_TX_EN_N_M2F        = CAN_TX_EN_N_M2F_net_1;
assign GPIO_0_M2F_net_1       = GPIO_0_M2F_net_0;
assign GPIO_0_M2F             = GPIO_0_M2F_net_1;
assign GPIO_1_M2F_net_1       = GPIO_1_M2F_net_0;
assign GPIO_1_M2F             = GPIO_1_M2F_net_1;
assign GPIO_3_M2F_net_1       = GPIO_3_M2F_net_0;
assign GPIO_3_M2F             = GPIO_3_M2F_net_1;
assign GPIO_5_M2F_net_1       = GPIO_5_M2F_net_0;
assign GPIO_5_M2F             = GPIO_5_M2F_net_1;
assign GPIO_7_M2F_net_1       = GPIO_7_M2F_net_0;
assign GPIO_7_M2F             = GPIO_7_M2F_net_1;
assign GPIO_8_M2F_net_1       = GPIO_8_M2F_net_0;
assign GPIO_8_M2F             = GPIO_8_M2F_net_1;
assign GPIO_9_M2F_net_1       = GPIO_9_M2F_net_0;
assign GPIO_9_M2F             = GPIO_9_M2F_net_1;
assign GPIO_10_M2F_net_1      = GPIO_10_M2F_net_0;
assign GPIO_10_M2F            = GPIO_10_M2F_net_1;
assign GPIO_11_M2F_net_1      = GPIO_11_M2F_net_0;
assign GPIO_11_M2F            = GPIO_11_M2F_net_1;
assign GPIO_12_M2F_net_1      = GPIO_12_M2F_net_0;
assign GPIO_12_M2F            = GPIO_12_M2F_net_1;
assign enable_master_net_1    = enable_master_net_0;
assign enable_master          = enable_master_net_1;
assign m_mosi_net_1           = m_mosi_net_0;
assign m_mosi                 = m_mosi_net_1;
assign m_sck_net_1            = m_sck_net_0;
assign m_sck                  = m_sck_net_1;
assign m_ss_net_1             = m_ss_net_0;
assign m_ss[7:0]              = m_ss_net_1;
assign SPISDO_net_1           = SPISDO_net_0;
assign SPISDO                 = SPISDO_net_1;
assign SPISCLKO_net_1         = SPISCLKO_net_0;
assign SPISCLKO               = SPISCLKO_net_1;
assign SPISS_net_1            = SPISS_net_0;
assign SPISS[7:0]             = SPISS_net_1;
//--------------------------------------------------------------------
// Concatenation assignments
//--------------------------------------------------------------------
assign MSS_INT_F2M_net_0 = { 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , OR3_0_Y , CORESPI_0_0_intr_or_0_Y };
//--------------------------------------------------------------------
// Bus Interface Nets Assignments - Unequal Pin Widths
//--------------------------------------------------------------------
assign CoreAPB3_0_APBmslave0_PADDR_0_6to0 = CoreAPB3_0_APBmslave0_PADDR[6:0];
assign CoreAPB3_0_APBmslave0_PADDR_0 = { CoreAPB3_0_APBmslave0_PADDR_0_6to0 };
assign CoreAPB3_0_APBmslave0_PADDR_1_6to0 = CoreAPB3_0_APBmslave0_PADDR[6:0];
assign CoreAPB3_0_APBmslave0_PADDR_1 = { CoreAPB3_0_APBmslave0_PADDR_1_6to0 };

assign CoreAPB3_0_APBmslave0_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_0_APBmslave0_PRDATA_0_7to0 = CoreAPB3_0_APBmslave0_PRDATA[7:0];
assign CoreAPB3_0_APBmslave0_PRDATA_0 = { CoreAPB3_0_APBmslave0_PRDATA_0_31to8, CoreAPB3_0_APBmslave0_PRDATA_0_7to0 };

assign CoreAPB3_0_APBmslave0_PWDATA_0_7to0 = CoreAPB3_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_0_APBmslave0_PWDATA_0 = { CoreAPB3_0_APBmslave0_PWDATA_0_7to0 };
assign CoreAPB3_0_APBmslave0_PWDATA_1_7to0 = CoreAPB3_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_0_APBmslave0_PWDATA_1 = { CoreAPB3_0_APBmslave0_PWDATA_1_7to0 };

assign CoreAPB3_0_APBmslave1_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_0_APBmslave1_PRDATA_0_7to0 = CoreAPB3_0_APBmslave1_PRDATA[7:0];
assign CoreAPB3_0_APBmslave1_PRDATA_0 = { CoreAPB3_0_APBmslave1_PRDATA_0_31to8, CoreAPB3_0_APBmslave1_PRDATA_0_7to0 };

//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------cdh_tsat5_system_sb_CCC_0_FCCC   -   Actel:SgCore:FCCC:2.0.201
cdh_tsat5_system_sb_CCC_0_FCCC CCC_0(
        // Inputs
        .RCOSC_25_50MHZ ( FABOSC_0_RCOSC_25_50MHZ_CCC_OUT_RCOSC_25_50MHZ_CCC ),
        // Outputs
        .GL0            ( FAB_CCC_GL0_net_0 ),
        .LOCK           ( FAB_CCC_LOCK_net_0 ) 
        );

//--------cdh_tsat5_system_sb_MSS
cdh_tsat5_system_sb_MSS cdh_tsat5_system_sb_MSS_0(
        // Inputs
        .MCCC_CLK_BASE          ( FAB_CCC_GL0_net_0 ),
        .MMUART_0_RXD_F2M       ( MMUART_0_RXD_F2M ),
        .MCCC_CLK_BASE_PLL_LOCK ( FAB_CCC_LOCK_net_0 ),
        .MSS_RESET_N_F2M        ( CORERESETP_0_RESET_N_F2M ),
        .CAN_RX_F2M             ( CAN_RX_F2M ),
        .FIC_0_APB_M_PREADY     ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PREADY ),
        .FIC_0_APB_M_PSLVERR    ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PSLVERR ),
        .FIC_2_APB_M_PREADY     ( VCC_net ), // tied to 1'b1 from definition
        .FIC_2_APB_M_PSLVERR    ( GND_net ), // tied to 1'b0 from definition
        .GPIO_5_F2M             ( GPIO_Input ),
        .MSS_INT_F2M            ( MSS_INT_F2M_net_0 ),
        .FIC_0_APB_M_PRDATA     ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PRDATA ),
        .FIC_2_APB_M_PRDATA     ( FIC_2_APB_M_PRDATA_const_net_0 ), // tied to 32'h00000000 from definition
        // Outputs
        .MMUART_0_TXD_M2F       ( MMUART_0_TXD_M2F_net_0 ),
        .MSS_RESET_N_M2F        ( cdh_tsat5_system_sb_MSS_TMP_0_MSS_RESET_N_M2F ),
        .CAN_TX_M2F             ( CAN_TX_M2F_net_0 ),
        .CAN_TX_EN_N_M2F        ( CAN_TX_EN_N_M2F_net_0 ),
        .GPIO_0_M2F             ( GPIO_0_M2F_net_0 ),
        .GPIO_1_M2F             ( GPIO_1_M2F_net_0 ),
        .GPIO_3_M2F             ( GPIO_3_M2F_net_0 ),
        .GPIO_5_M2F             ( GPIO_5_M2F_net_0 ),
        .GPIO_8_M2F             ( GPIO_8_M2F_net_0 ),
        .GPIO_9_M2F             ( GPIO_9_M2F_net_0 ),
        .GPIO_10_M2F            ( GPIO_10_M2F_net_0 ),
        .GPIO_11_M2F            ( GPIO_11_M2F_net_0 ),
        .GPIO_12_M2F            ( GPIO_12_M2F_net_0 ),
        .FIC_0_APB_M_PSEL       ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PSELx ),
        .FIC_0_APB_M_PWRITE     ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PWRITE ),
        .FIC_0_APB_M_PENABLE    ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PENABLE ),
        .FIC_2_APB_M_PRESET_N   ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_2_APB_M_PRESET_N ),
        .FIC_2_APB_M_PCLK       (  ),
        .FIC_2_APB_M_PWRITE     (  ),
        .FIC_2_APB_M_PENABLE    (  ),
        .FIC_2_APB_M_PSEL       (  ),
        .GPIO_5_M2F_OE          ( GPIO_7_M2F_net_0 ),
        .FIC_0_APB_M_PADDR      ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PADDR ),
        .FIC_0_APB_M_PWDATA     ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PWDATA ),
        .FIC_2_APB_M_PADDR      (  ),
        .FIC_2_APB_M_PWDATA     (  ) 
        );

//--------CoreAPB3   -   Actel:DirectCore:CoreAPB3:4.1.100
CoreAPB3 #( 
        .APB_DWIDTH      ( 32 ),
        .APBSLOT0ENABLE  ( 1 ),
        .APBSLOT1ENABLE  ( 1 ),
        .APBSLOT2ENABLE  ( 0 ),
        .APBSLOT3ENABLE  ( 0 ),
        .APBSLOT4ENABLE  ( 0 ),
        .APBSLOT5ENABLE  ( 0 ),
        .APBSLOT6ENABLE  ( 0 ),
        .APBSLOT7ENABLE  ( 0 ),
        .APBSLOT8ENABLE  ( 0 ),
        .APBSLOT9ENABLE  ( 0 ),
        .APBSLOT10ENABLE ( 0 ),
        .APBSLOT11ENABLE ( 0 ),
        .APBSLOT12ENABLE ( 0 ),
        .APBSLOT13ENABLE ( 0 ),
        .APBSLOT14ENABLE ( 0 ),
        .APBSLOT15ENABLE ( 0 ),
        .FAMILY          ( 19 ),
        .IADDR_OPTION    ( 0 ),
        .MADDR_BITS      ( 20 ),
        .SC_0            ( 0 ),
        .SC_1            ( 0 ),
        .SC_2            ( 0 ),
        .SC_3            ( 0 ),
        .SC_4            ( 0 ),
        .SC_5            ( 0 ),
        .SC_6            ( 0 ),
        .SC_7            ( 0 ),
        .SC_8            ( 0 ),
        .SC_9            ( 0 ),
        .SC_10           ( 0 ),
        .SC_11           ( 0 ),
        .SC_12           ( 0 ),
        .SC_13           ( 0 ),
        .SC_14           ( 0 ),
        .SC_15           ( 0 ),
        .UPR_NIBBLE_POSN ( 3 ) )
CoreAPB3_0(
        // Inputs
        .PRESETN    ( GND_net ), // tied to 1'b0 from definition
        .PCLK       ( GND_net ), // tied to 1'b0 from definition
        .PWRITE     ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PWRITE ),
        .PENABLE    ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PENABLE ),
        .PSEL       ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PSELx ),
        .PREADYS0   ( CoreAPB3_0_APBmslave0_PREADY ),
        .PSLVERRS0  ( CoreAPB3_0_APBmslave0_PSLVERR ),
        .PREADYS1   ( CoreAPB3_0_APBmslave1_PREADY ),
        .PSLVERRS1  ( CoreAPB3_0_APBmslave1_PSLVERR ),
        .PREADYS2   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS2  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS3   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS3  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS4   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS4  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS5   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS5  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS6   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS6  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS7   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS7  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS8   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS8  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS9   ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS9  ( GND_net ), // tied to 1'b0 from definition
        .PREADYS10  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS10 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS11  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS11 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS12  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS12 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS13  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS13 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS14  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS14 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS15  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS15 ( GND_net ), // tied to 1'b0 from definition
        .PREADYS16  ( VCC_net ), // tied to 1'b1 from definition
        .PSLVERRS16 ( GND_net ), // tied to 1'b0 from definition
        .PADDR      ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PADDR ),
        .PWDATA     ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PWDATA ),
        .PRDATAS0   ( CoreAPB3_0_APBmslave0_PRDATA_0 ),
        .PRDATAS1   ( CoreAPB3_0_APBmslave1_PRDATA_0 ),
        .PRDATAS2   ( PRDATAS2_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS3   ( PRDATAS3_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS4   ( PRDATAS4_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS5   ( PRDATAS5_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS6   ( PRDATAS6_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS7   ( PRDATAS7_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS8   ( PRDATAS8_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS9   ( PRDATAS9_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS10  ( PRDATAS10_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS11  ( PRDATAS11_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS12  ( PRDATAS12_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS13  ( PRDATAS13_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS14  ( PRDATAS14_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS15  ( PRDATAS15_const_net_0 ), // tied to 32'h00000000 from definition
        .PRDATAS16  ( PRDATAS16_const_net_0 ), // tied to 32'h00000000 from definition
        .IADDR      ( IADDR_const_net_0 ), // tied to 32'h00000000 from definition
        // Outputs
        .PREADY     ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PREADY ),
        .PSLVERR    ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PSLVERR ),
        .PWRITES    ( CoreAPB3_0_APBmslave0_PWRITE ),
        .PENABLES   ( CoreAPB3_0_APBmslave0_PENABLE ),
        .PSELS0     ( CoreAPB3_0_APBmslave0_PSELx ),
        .PSELS1     ( CoreAPB3_0_APBmslave1_PSELx ),
        .PSELS2     (  ),
        .PSELS3     (  ),
        .PSELS4     (  ),
        .PSELS5     (  ),
        .PSELS6     (  ),
        .PSELS7     (  ),
        .PSELS8     (  ),
        .PSELS9     (  ),
        .PSELS10    (  ),
        .PSELS11    (  ),
        .PSELS12    (  ),
        .PSELS13    (  ),
        .PSELS14    (  ),
        .PSELS15    (  ),
        .PSELS16    (  ),
        .PRDATA     ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_0_APB_MASTER_PRDATA ),
        .PADDRS     ( CoreAPB3_0_APBmslave0_PADDR ),
        .PWDATAS    ( CoreAPB3_0_APBmslave0_PWDATA ) 
        );

//--------CoreResetP   -   Actel:DirectCore:CoreResetP:7.1.100
CoreResetP #( 
        .DDR_WAIT            ( 200 ),
        .DEVICE_090          ( 0 ),
        .DEVICE_VOLTAGE      ( 2 ),
        .ENABLE_SOFT_RESETS  ( 0 ),
        .EXT_RESET_CFG       ( 0 ),
        .FDDR_IN_USE         ( 0 ),
        .MDDR_IN_USE         ( 0 ),
        .SDIF0_IN_USE        ( 0 ),
        .SDIF0_PCIE          ( 0 ),
        .SDIF0_PCIE_HOTRESET ( 1 ),
        .SDIF0_PCIE_L2P2     ( 1 ),
        .SDIF1_IN_USE        ( 0 ),
        .SDIF1_PCIE          ( 0 ),
        .SDIF1_PCIE_HOTRESET ( 1 ),
        .SDIF1_PCIE_L2P2     ( 1 ),
        .SDIF2_IN_USE        ( 0 ),
        .SDIF2_PCIE          ( 0 ),
        .SDIF2_PCIE_HOTRESET ( 1 ),
        .SDIF2_PCIE_L2P2     ( 1 ),
        .SDIF3_IN_USE        ( 0 ),
        .SDIF3_PCIE          ( 0 ),
        .SDIF3_PCIE_HOTRESET ( 1 ),
        .SDIF3_PCIE_L2P2     ( 1 ) )
CORERESETP_0(
        // Inputs
        .RESET_N_M2F                    ( cdh_tsat5_system_sb_MSS_TMP_0_MSS_RESET_N_M2F ),
        .FIC_2_APB_M_PRESET_N           ( cdh_tsat5_system_sb_MSS_TMP_0_FIC_2_APB_M_PRESET_N ),
        .POWER_ON_RESET_N               ( POWER_ON_RESET_N_net_0 ),
        .FAB_RESET_N                    ( FAB_RESET_N ),
        .RCOSC_25_50MHZ                 ( FABOSC_0_RCOSC_25_50MHZ_O2F ),
        .CLK_BASE                       ( FAB_CCC_GL0_net_0 ),
        .CLK_LTSSM                      ( GND_net ), // tied to 1'b0 from definition
        .FPLL_LOCK                      ( VCC_net ), // tied to 1'b1 from definition
        .SDIF0_SPLL_LOCK                ( VCC_net ), // tied to 1'b1 from definition
        .SDIF1_SPLL_LOCK                ( VCC_net ), // tied to 1'b1 from definition
        .SDIF2_SPLL_LOCK                ( VCC_net ), // tied to 1'b1 from definition
        .SDIF3_SPLL_LOCK                ( VCC_net ), // tied to 1'b1 from definition
        .CONFIG1_DONE                   ( VCC_net ),
        .CONFIG2_DONE                   ( VCC_net ),
        .SDIF0_PERST_N                  ( VCC_net ), // tied to 1'b1 from definition
        .SDIF1_PERST_N                  ( VCC_net ), // tied to 1'b1 from definition
        .SDIF2_PERST_N                  ( VCC_net ), // tied to 1'b1 from definition
        .SDIF3_PERST_N                  ( VCC_net ), // tied to 1'b1 from definition
        .SDIF0_PSEL                     ( GND_net ), // tied to 1'b0 from definition
        .SDIF0_PWRITE                   ( VCC_net ), // tied to 1'b1 from definition
        .SDIF1_PSEL                     ( GND_net ), // tied to 1'b0 from definition
        .SDIF1_PWRITE                   ( VCC_net ), // tied to 1'b1 from definition
        .SDIF2_PSEL                     ( GND_net ), // tied to 1'b0 from definition
        .SDIF2_PWRITE                   ( VCC_net ), // tied to 1'b1 from definition
        .SDIF3_PSEL                     ( GND_net ), // tied to 1'b0 from definition
        .SDIF3_PWRITE                   ( VCC_net ), // tied to 1'b1 from definition
        .SOFT_EXT_RESET_OUT             ( GND_net ), // tied to 1'b0 from definition
        .SOFT_RESET_F2M                 ( GND_net ), // tied to 1'b0 from definition
        .SOFT_M3_RESET                  ( GND_net ), // tied to 1'b0 from definition
        .SOFT_MDDR_DDR_AXI_S_CORE_RESET ( GND_net ), // tied to 1'b0 from definition
        .SOFT_FDDR_CORE_RESET           ( GND_net ), // tied to 1'b0 from definition
        .SOFT_SDIF0_PHY_RESET           ( GND_net ), // tied to 1'b0 from definition
        .SOFT_SDIF0_CORE_RESET          ( GND_net ), // tied to 1'b0 from definition
        .SOFT_SDIF0_0_CORE_RESET        ( GND_net ), // tied to 1'b0 from definition
        .SOFT_SDIF0_1_CORE_RESET        ( GND_net ), // tied to 1'b0 from definition
        .SOFT_SDIF1_PHY_RESET           ( GND_net ), // tied to 1'b0 from definition
        .SOFT_SDIF1_CORE_RESET          ( GND_net ), // tied to 1'b0 from definition
        .SOFT_SDIF2_PHY_RESET           ( GND_net ), // tied to 1'b0 from definition
        .SOFT_SDIF2_CORE_RESET          ( GND_net ), // tied to 1'b0 from definition
        .SOFT_SDIF3_PHY_RESET           ( GND_net ), // tied to 1'b0 from definition
        .SOFT_SDIF3_CORE_RESET          ( GND_net ), // tied to 1'b0 from definition
        .SDIF0_PRDATA                   ( SDIF0_PRDATA_const_net_0 ), // tied to 32'h00000000 from definition
        .SDIF1_PRDATA                   ( SDIF1_PRDATA_const_net_0 ), // tied to 32'h00000000 from definition
        .SDIF2_PRDATA                   ( SDIF2_PRDATA_const_net_0 ), // tied to 32'h00000000 from definition
        .SDIF3_PRDATA                   ( SDIF3_PRDATA_const_net_0 ), // tied to 32'h00000000 from definition
        // Outputs
        .MSS_HPMS_READY                 ( MSS_READY_net_0 ),
        .DDR_READY                      (  ),
        .SDIF_READY                     (  ),
        .RESET_N_F2M                    ( CORERESETP_0_RESET_N_F2M ),
        .M3_RESET_N                     (  ),
        .EXT_RESET_OUT                  (  ),
        .MDDR_DDR_AXI_S_CORE_RESET_N    (  ),
        .FDDR_CORE_RESET_N              (  ),
        .SDIF0_CORE_RESET_N             (  ),
        .SDIF0_0_CORE_RESET_N           (  ),
        .SDIF0_1_CORE_RESET_N           (  ),
        .SDIF0_PHY_RESET_N              (  ),
        .SDIF1_CORE_RESET_N             (  ),
        .SDIF1_PHY_RESET_N              (  ),
        .SDIF2_CORE_RESET_N             (  ),
        .SDIF2_PHY_RESET_N              (  ),
        .SDIF3_CORE_RESET_N             (  ),
        .SDIF3_PHY_RESET_N              (  ),
        .SDIF_RELEASED                  (  ),
        .INIT_DONE                      ( INIT_DONE_net_0 ) 
        );

//--------CORESPI1_1
CORESPI1_1 CORESPI1_1_0(
        // Inputs
        .PCLK       ( FAB_CCC_GL0_net_0 ),
        .PRESETN    ( MSS_READY_net_0 ),
        .SPISSI     ( GND_net ),
        .SPISDI     ( SPISDI ),
        .SPICLKI    ( GND_net ),
        .PADDR      ( CoreAPB3_0_APBmslave0_PADDR_1 ),
        .PSEL       ( CoreAPB3_0_APBmslave1_PSELx ),
        .PENABLE    ( CoreAPB3_0_APBmslave0_PENABLE ),
        .PWRITE     ( CoreAPB3_0_APBmslave0_PWRITE ),
        .PWDATA     ( CoreAPB3_0_APBmslave0_PWDATA_1 ),
        // Outputs
        .SPIINT     ( CORESPI1_1_0_SPIINT ),
        .SPIRXAVAIL ( CORESPI1_1_0_SPIRXAVAIL ),
        .SPITXRFM   ( CORESPI1_1_0_SPITXRFM ),
        .SPISS      ( SPISS_net_0 ),
        .SPISCLKO   ( SPISCLKO_net_0 ),
        .SPIOEN     (  ),
        .SPISDO     ( SPISDO_net_0 ),
        .SPIMODE    (  ),
        .PRDATA     ( CoreAPB3_0_APBmslave1_PRDATA ),
        .PREADY     ( CoreAPB3_0_APBmslave1_PREADY ),
        .PSLVERR    ( CoreAPB3_0_APBmslave1_PSLVERR ) 
        );

//--------CORESPI   -   Actel:DirectCore:CORESPI:5.2.104
CORESPI #( 
        .APB_DWIDTH        ( 8 ),
        .CFG_CLK           ( 255 ),
        .CFG_FIFO_DEPTH    ( 8 ),
        .CFG_FRAME_SIZE    ( 8 ),
        .CFG_MODE          ( 0 ),
        .CFG_MOT_MODE      ( 0 ),
        .CFG_MOT_SSEL      ( 1 ),
        .CFG_NSC_OPERATION ( 0 ),
        .CFG_TI_JMB_FRAMES ( 0 ),
        .CFG_TI_NSC_CUSTOM ( 0 ),
        .CFG_TI_NSC_FRC    ( 0 ) )
CORESPI_0_0(
        // Inputs
        .PCLK       ( FAB_CCC_GL0_net_0 ),
        .PRESETN    ( MSS_READY_net_0 ),
        .PSEL       ( CoreAPB3_0_APBmslave0_PSELx ),
        .PENABLE    ( CoreAPB3_0_APBmslave0_PENABLE ),
        .PWRITE     ( CoreAPB3_0_APBmslave0_PWRITE ),
        .SPISSI     ( GND_net ),
        .SPISDI     ( m_miso ),
        .SPICLKI    ( GND_net ),
        .PADDR      ( CoreAPB3_0_APBmslave0_PADDR_0 ),
        .PWDATA     ( CoreAPB3_0_APBmslave0_PWDATA_0 ),
        // Outputs
        .PREADY     ( CoreAPB3_0_APBmslave0_PREADY ),
        .PSLVERR    ( CoreAPB3_0_APBmslave0_PSLVERR ),
        .SPIINT     ( CORESPI_0_0_SPIINT ),
        .SPIRXAVAIL ( CORESPI_0_0_SPIRXAVAIL ),
        .SPITXRFM   ( CORESPI_0_0_SPITXRFM ),
        .SPISCLKO   ( m_sck_net_0 ),
        .SPIOEN     ( enable_master_net_0 ),
        .SPISDO     ( m_mosi_net_0 ),
        .SPIMODE    (  ),
        .PRDATA     ( CoreAPB3_0_APBmslave0_PRDATA ),
        .SPISS      ( m_ss_net_0 ) 
        );

//--------OR3
OR3 CORESPI_0_0_intr_or_0(
        // Inputs
        .A ( CORESPI_0_0_SPIINT ),
        .B ( CORESPI_0_0_SPIRXAVAIL ),
        .C ( CORESPI_0_0_SPITXRFM ),
        // Outputs
        .Y ( CORESPI_0_0_intr_or_0_Y ) 
        );

//--------cdh_tsat5_system_sb_FABOSC_0_OSC   -   Actel:SgCore:OSC:2.0.101
cdh_tsat5_system_sb_FABOSC_0_OSC FABOSC_0(
        // Inputs
        .XTL                ( GND_net ), // tied to 1'b0 from definition
        // Outputs
        .RCOSC_25_50MHZ_CCC ( FABOSC_0_RCOSC_25_50MHZ_CCC_OUT_RCOSC_25_50MHZ_CCC ),
        .RCOSC_25_50MHZ_O2F ( FABOSC_0_RCOSC_25_50MHZ_O2F ),
        .RCOSC_1MHZ_CCC     (  ),
        .RCOSC_1MHZ_O2F     (  ),
        .XTLOSC_CCC         (  ),
        .XTLOSC_O2F         (  ) 
        );

//--------OR3
OR3 OR3_0(
        // Inputs
        .A ( CORESPI1_1_0_SPIINT ),
        .B ( CORESPI1_1_0_SPIRXAVAIL ),
        .C ( CORESPI1_1_0_SPITXRFM ),
        // Outputs
        .Y ( OR3_0_Y ) 
        );

//--------SYSRESET
SYSRESET SYSRESET_POR(
        // Inputs
        .DEVRST_N         ( DEVRST_N ),
        // Outputs
        .POWER_ON_RESET_N ( POWER_ON_RESET_N_net_0 ) 
        );


endmodule
