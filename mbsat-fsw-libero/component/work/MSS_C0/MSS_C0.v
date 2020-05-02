//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Fri May  1 16:42:36 2020
// Version: v12.1 12.600.0.14
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// MSS_C0
module MSS_C0(
    // Inputs
    CAN_RX_F2M,
    DEVRST_N,
    MMUART_0_RXD_F2M,
    SPISDI,
    SPISDI_0,
    SPI_0_DI,
    // Outputs
    CAN_TX_M2F,
    GPIO_0_M2F,
    GPIO_1_M2F,
    GPIO_3_M2F,
    GPIO_5_M2F,
    GPIO_6_M2F,
    GPIO_7_M2F,
    MMUART_0_TXD_M2F,
    SPISCLKO,
    SPISCLKO_0,
    SPISDO,
    SPISDO_0,
    SPISS,
    SPISS_0,
    SPI_0_DO,
    // Inouts
    SPI_0_CLK,
    SPI_0_SS0
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  CAN_RX_F2M;
input  DEVRST_N;
input  MMUART_0_RXD_F2M;
input  SPISDI;
input  SPISDI_0;
input  SPI_0_DI;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output CAN_TX_M2F;
output GPIO_0_M2F;
output GPIO_1_M2F;
output GPIO_3_M2F;
output GPIO_5_M2F;
output GPIO_6_M2F;
output GPIO_7_M2F;
output MMUART_0_TXD_M2F;
output SPISCLKO;
output SPISCLKO_0;
output SPISDO;
output SPISDO_0;
output SPISS;
output SPISS_0;
output SPI_0_DO;
//--------------------------------------------------------------------
// Inout
//--------------------------------------------------------------------
inout  SPI_0_CLK;
inout  SPI_0_SS0;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
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
wire          CoreResetP_C0_0_M3_RESET_N;
wire          CoreResetP_C0_0_MSS_HPMS_READY;
wire          CoreResetP_C0_0_RESET_N_F2M;
wire          CORESPI_C0_0_SPIINT;
wire          CORESPI_C0_0_SPIRXAVAIL;
wire          CORESPI_C0_0_SPITXRFM;
wire          CORESPI_C1_0_SPIINT;
wire          CORESPI_C1_0_SPIRXAVAIL;
wire          CORESPI_C1_0_SPITXRFM;
wire          DEVRST_N;
wire          FCCC_C0_0_GL0;
wire          FCCC_C0_0_LOCK;
wire          GPIO_0_M2F_net_0;
wire          GPIO_1_M2F_net_0;
wire          GPIO_3_M2F_net_0;
wire          GPIO_5_M2F_net_0;
wire          GPIO_6_M2F_net_0;
wire          GPIO_7_M2F_net_0;
wire          MMUART_0_RXD_F2M;
wire          MMUART_0_TXD_M2F_net_0;
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
wire          OSC_C0_0_RCOSC_25_50MHZ_CCC_OUT_RCOSC_25_50MHZ_CCC;
wire          OSC_C0_0_RCOSC_25_50MHZ_O2F;
wire          SPI_0_CLK;
wire          SPI_0_DI;
wire          SPI_0_DO_net_0;
wire          SPI_0_SS0;
wire          SPISCLKO_net_0;
wire          SPISCLKO_0_net_0;
wire          SPISDI;
wire          SPISDI_0;
wire          SPISDO_net_0;
wire          SPISDO_0_net_0;
wire   [0:0]  SPISS_net_0;
wire   [0:0]  SPISS_0_net_0;
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
wire          SPISS_net_1;
wire          SPISCLKO_net_1;
wire          SPISDO_net_1;
wire          SPISS_0_net_1;
wire          SPISCLKO_0_net_1;
wire          SPISDO_0_net_1;
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
wire   [7:0]  SPISS_net_2;
wire   [7:0]  SPISS_net_3;
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
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_1_6to0;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_1;
wire   [31:0] CoreAPB3_C0_0_APBmslave0_PADDR;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_0_6to0;
wire   [6:0]  CoreAPB3_C0_0_APBmslave0_PADDR_0;
wire   [31:8] CoreAPB3_C0_0_APBmslave0_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_C0_0_APBmslave0_PRDATA_0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PRDATA;
wire   [31:0] CoreAPB3_C0_0_APBmslave0_PWDATA;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_1_7to0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_1;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_0_7to0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave0_PWDATA_0;
wire   [7:0]  CoreAPB3_C0_0_APBmslave1_PRDATA;
wire   [31:8] CoreAPB3_C0_0_APBmslave1_PRDATA_0_31to8;
wire   [7:0]  CoreAPB3_C0_0_APBmslave1_PRDATA_0_7to0;
wire   [31:0] CoreAPB3_C0_0_APBmslave1_PRDATA_0;
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
assign SPISS_net_1            = SPISS_net_0[0];
assign SPISS                  = SPISS_net_1;
assign SPISCLKO_net_1         = SPISCLKO_net_0;
assign SPISCLKO               = SPISCLKO_net_1;
assign SPISDO_net_1           = SPISDO_net_0;
assign SPISDO                 = SPISDO_net_1;
assign SPISS_0_net_1          = SPISS_0_net_0[0];
assign SPISS_0                = SPISS_0_net_1;
assign SPISCLKO_0_net_1       = SPISCLKO_0_net_0;
assign SPISCLKO_0             = SPISCLKO_0_net_1;
assign SPISDO_0_net_1         = SPISDO_0_net_0;
assign SPISDO_0               = SPISDO_0_net_1;
//--------------------------------------------------------------------
// Slices assignments
//--------------------------------------------------------------------
assign SPISS_net_0[0]    = SPISS_net_2[0:0];
assign SPISS_0_net_0[0]  = SPISS_net_3[0:0];
assign SPISS_slice_0[1]  = SPISS_net_2[1:1];
assign SPISS_slice_1[2]  = SPISS_net_2[2:2];
assign SPISS_slice_2[3]  = SPISS_net_2[3:3];
assign SPISS_slice_3[4]  = SPISS_net_2[4:4];
assign SPISS_slice_4[5]  = SPISS_net_2[5:5];
assign SPISS_slice_5[6]  = SPISS_net_2[6:6];
assign SPISS_slice_6[7]  = SPISS_net_2[7:7];
assign SPISS_slice_7[1]  = SPISS_net_3[1:1];
assign SPISS_slice_8[2]  = SPISS_net_3[2:2];
assign SPISS_slice_9[3]  = SPISS_net_3[3:3];
assign SPISS_slice_10[4] = SPISS_net_3[4:4];
assign SPISS_slice_11[5] = SPISS_net_3[5:5];
assign SPISS_slice_12[6] = SPISS_net_3[6:6];
assign SPISS_slice_13[7] = SPISS_net_3[7:7];
//--------------------------------------------------------------------
// Concatenation assignments
//--------------------------------------------------------------------
assign MSS_INT_F2M_net_0 = { 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , 1'b0 , OR3_1_Y , OR3_0_Y };
//--------------------------------------------------------------------
// Bus Interface Nets Assignments - Unequal Pin Widths
//--------------------------------------------------------------------
assign CoreAPB3_C0_0_APBmslave0_PADDR_1_6to0 = CoreAPB3_C0_0_APBmslave0_PADDR[6:0];
assign CoreAPB3_C0_0_APBmslave0_PADDR_1 = { CoreAPB3_C0_0_APBmslave0_PADDR_1_6to0 };
assign CoreAPB3_C0_0_APBmslave0_PADDR_0_6to0 = CoreAPB3_C0_0_APBmslave0_PADDR[6:0];
assign CoreAPB3_C0_0_APBmslave0_PADDR_0 = { CoreAPB3_C0_0_APBmslave0_PADDR_0_6to0 };

assign CoreAPB3_C0_0_APBmslave0_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_C0_0_APBmslave0_PRDATA_0_7to0 = CoreAPB3_C0_0_APBmslave0_PRDATA[7:0];
assign CoreAPB3_C0_0_APBmslave0_PRDATA_0 = { CoreAPB3_C0_0_APBmslave0_PRDATA_0_31to8, CoreAPB3_C0_0_APBmslave0_PRDATA_0_7to0 };

assign CoreAPB3_C0_0_APBmslave0_PWDATA_1_7to0 = CoreAPB3_C0_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_C0_0_APBmslave0_PWDATA_1 = { CoreAPB3_C0_0_APBmslave0_PWDATA_1_7to0 };
assign CoreAPB3_C0_0_APBmslave0_PWDATA_0_7to0 = CoreAPB3_C0_0_APBmslave0_PWDATA[7:0];
assign CoreAPB3_C0_0_APBmslave0_PWDATA_0 = { CoreAPB3_C0_0_APBmslave0_PWDATA_0_7to0 };

assign CoreAPB3_C0_0_APBmslave1_PRDATA_0_31to8 = 24'h0;
assign CoreAPB3_C0_0_APBmslave1_PRDATA_0_7to0 = CoreAPB3_C0_0_APBmslave1_PRDATA[7:0];
assign CoreAPB3_C0_0_APBmslave1_PRDATA_0 = { CoreAPB3_C0_0_APBmslave1_PRDATA_0_31to8, CoreAPB3_C0_0_APBmslave1_PRDATA_0_7to0 };

//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------CoreAPB3_C0
CoreAPB3_C0 CoreAPB3_C0_0(
        // Inputs
        .PADDR     ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PADDR ),
        .PSEL      ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PSELx ),
        .PENABLE   ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PENABLE ),
        .PWRITE    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PWRITE ),
        .PWDATA    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PWDATA ),
        .PRDATAS0  ( CoreAPB3_C0_0_APBmslave0_PRDATA_0 ),
        .PREADYS0  ( CoreAPB3_C0_0_APBmslave0_PREADY ),
        .PSLVERRS0 ( CoreAPB3_C0_0_APBmslave0_PSLVERR ),
        .PRDATAS1  ( CoreAPB3_C0_0_APBmslave1_PRDATA_0 ),
        .PREADYS1  ( CoreAPB3_C0_0_APBmslave1_PREADY ),
        .PSLVERRS1 ( CoreAPB3_C0_0_APBmslave1_PSLVERR ),
        // Outputs
        .PRDATA    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PRDATA ),
        .PREADY    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PREADY ),
        .PSLVERR   ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PSLVERR ),
        .PADDRS    ( CoreAPB3_C0_0_APBmslave0_PADDR ),
        .PSELS0    ( CoreAPB3_C0_0_APBmslave0_PSELx ),
        .PENABLES  ( CoreAPB3_C0_0_APBmslave0_PENABLE ),
        .PWRITES   ( CoreAPB3_C0_0_APBmslave0_PWRITE ),
        .PWDATAS   ( CoreAPB3_C0_0_APBmslave0_PWDATA ),
        .PSELS1    ( CoreAPB3_C0_0_APBmslave1_PSELx ) 
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
        .SPISDI     ( SPISDI ),
        .SPICLKI    ( GND_net ),
        .PADDR      ( CoreAPB3_C0_0_APBmslave0_PADDR_0 ),
        .PSEL       ( CoreAPB3_C0_0_APBmslave0_PSELx ),
        .PENABLE    ( CoreAPB3_C0_0_APBmslave0_PENABLE ),
        .PWRITE     ( CoreAPB3_C0_0_APBmslave0_PWRITE ),
        .PWDATA     ( CoreAPB3_C0_0_APBmslave0_PWDATA_0 ),
        // Outputs
        .SPIINT     ( CORESPI_C0_0_SPIINT ),
        .SPIRXAVAIL ( CORESPI_C0_0_SPIRXAVAIL ),
        .SPITXRFM   ( CORESPI_C0_0_SPITXRFM ),
        .SPISS      ( SPISS_net_2 ),
        .SPISCLKO   ( SPISCLKO_net_0 ),
        .SPIOEN     (  ),
        .SPISDO     ( SPISDO_net_0 ),
        .SPIMODE    (  ),
        .PRDATA     ( CoreAPB3_C0_0_APBmslave0_PRDATA ),
        .PREADY     ( CoreAPB3_C0_0_APBmslave0_PREADY ),
        .PSLVERR    ( CoreAPB3_C0_0_APBmslave0_PSLVERR ) 
        );

//--------CORESPI_C1
CORESPI_C1 CORESPI_C1_0(
        // Inputs
        .PCLK       ( FCCC_C0_0_GL0 ),
        .PRESETN    ( CoreResetP_C0_0_MSS_HPMS_READY ),
        .SPISSI     ( GND_net ),
        .SPISDI     ( SPISDI_0 ),
        .SPICLKI    ( GND_net ),
        .PADDR      ( CoreAPB3_C0_0_APBmslave0_PADDR_1 ),
        .PSEL       ( CoreAPB3_C0_0_APBmslave1_PSELx ),
        .PENABLE    ( CoreAPB3_C0_0_APBmslave0_PENABLE ),
        .PWRITE     ( CoreAPB3_C0_0_APBmslave0_PWRITE ),
        .PWDATA     ( CoreAPB3_C0_0_APBmslave0_PWDATA_1 ),
        // Outputs
        .SPIINT     ( CORESPI_C1_0_SPIINT ),
        .SPIRXAVAIL ( CORESPI_C1_0_SPIRXAVAIL ),
        .SPITXRFM   ( CORESPI_C1_0_SPITXRFM ),
        .SPISS      ( SPISS_net_3 ),
        .SPISCLKO   ( SPISCLKO_0_net_0 ),
        .SPIOEN     (  ),
        .SPISDO     ( SPISDO_0_net_0 ),
        .SPIMODE    (  ),
        .PRDATA     ( CoreAPB3_C0_0_APBmslave1_PRDATA ),
        .PREADY     ( CoreAPB3_C0_0_APBmslave1_PREADY ),
        .PSLVERR    ( CoreAPB3_C0_0_APBmslave1_PSLVERR ) 
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
        .MSS_INT_F2M            ( MSS_INT_F2M_net_0 ),
        .FIC_0_APB_M_PRDATA     ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PRDATA ),
        .FIC_0_APB_M_PREADY     ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PREADY ),
        .FIC_0_APB_M_PSLVERR    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PSLVERR ),
        .FIC_2_APB_M_PRDATA     ( FIC_2_APB_M_PRDATA_const_net_0 ), // tied to 32'h00000000 from definition
        .FIC_2_APB_M_PREADY     ( VCC_net ), // tied to 1'b1 from definition
        .FIC_2_APB_M_PSLVERR    ( GND_net ), // tied to 1'b0 from definition
        .M3_RESET_N             ( CoreResetP_C0_0_M3_RESET_N ),
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
        .FIC_0_APB_M_PADDR      ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PADDR ),
        .FIC_0_APB_M_PSEL       ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PSELx ),
        .FIC_0_APB_M_PWRITE     ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PWRITE ),
        .FIC_0_APB_M_PENABLE    ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PENABLE ),
        .FIC_0_APB_M_PWDATA     ( MSS_C0_MSS_0_FIC_0_APB_MASTER_PWDATA ),
        .FIC_2_APB_M_PRESET_N   ( MSS_C0_MSS_0_FIC_2_APB_M_PRESET_N ),
        .FIC_2_APB_M_PCLK       (  ),
        .FIC_2_APB_M_PADDR      (  ),
        .FIC_2_APB_M_PWDATA     (  ),
        .FIC_2_APB_M_PWRITE     (  ),
        .FIC_2_APB_M_PENABLE    (  ),
        .FIC_2_APB_M_PSEL       (  ),
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
