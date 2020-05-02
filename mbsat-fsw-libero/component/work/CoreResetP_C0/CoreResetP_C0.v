//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Fri May  1 16:22:34 2020
// Version: v12.1 12.600.0.14
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// CoreResetP_C0
module CoreResetP_C0(
    // Inputs
    CLK_BASE,
    CONFIG1_DONE,
    CONFIG2_DONE,
    FAB_RESET_N,
    FIC_2_APB_M_PRESET_N,
    FPLL_LOCK,
    POWER_ON_RESET_N,
    RCOSC_25_50MHZ,
    RESET_N_M2F,
    // Outputs
    DDR_READY,
    FDDR_CORE_RESET_N,
    INIT_DONE,
    M3_RESET_N,
    MSS_HPMS_READY,
    RESET_N_F2M
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  CLK_BASE;
input  CONFIG1_DONE;
input  CONFIG2_DONE;
input  FAB_RESET_N;
input  FIC_2_APB_M_PRESET_N;
input  FPLL_LOCK;
input  POWER_ON_RESET_N;
input  RCOSC_25_50MHZ;
input  RESET_N_M2F;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output DDR_READY;
output FDDR_CORE_RESET_N;
output INIT_DONE;
output M3_RESET_N;
output MSS_HPMS_READY;
output RESET_N_F2M;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   CLK_BASE;
wire   CONFIG1_DONE;
wire   CONFIG2_DONE;
wire   DDR_READY_net_0;
wire   FAB_RESET_N;
wire   FDDR_CORE_RESET_N_net_0;
wire   FIC_2_APB_M_PRESET_N;
wire   FPLL_LOCK;
wire   INIT_DONE_net_0;
wire   M3_RESET_N_net_0;
wire   MSS_HPMS_READY_net_0;
wire   POWER_ON_RESET_N;
wire   RCOSC_25_50MHZ;
wire   RESET_N_F2M_net_0;
wire   RESET_N_M2F;
wire   MSS_HPMS_READY_net_1;
wire   DDR_READY_net_1;
wire   RESET_N_F2M_net_1;
wire   M3_RESET_N_net_1;
wire   FDDR_CORE_RESET_N_net_1;
wire   INIT_DONE_net_1;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire   GND_net;
wire   VCC_net;
wire   [31:0]SDIF0_PRDATA_const_net_0;
wire   [31:0]SDIF1_PRDATA_const_net_0;
wire   [31:0]SDIF2_PRDATA_const_net_0;
wire   [31:0]SDIF3_PRDATA_const_net_0;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign GND_net                  = 1'b0;
assign VCC_net                  = 1'b1;
assign SDIF0_PRDATA_const_net_0 = 32'h00000000;
assign SDIF1_PRDATA_const_net_0 = 32'h00000000;
assign SDIF2_PRDATA_const_net_0 = 32'h00000000;
assign SDIF3_PRDATA_const_net_0 = 32'h00000000;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign MSS_HPMS_READY_net_1    = MSS_HPMS_READY_net_0;
assign MSS_HPMS_READY          = MSS_HPMS_READY_net_1;
assign DDR_READY_net_1         = DDR_READY_net_0;
assign DDR_READY               = DDR_READY_net_1;
assign RESET_N_F2M_net_1       = RESET_N_F2M_net_0;
assign RESET_N_F2M             = RESET_N_F2M_net_1;
assign M3_RESET_N_net_1        = M3_RESET_N_net_0;
assign M3_RESET_N              = M3_RESET_N_net_1;
assign FDDR_CORE_RESET_N_net_1 = FDDR_CORE_RESET_N_net_0;
assign FDDR_CORE_RESET_N       = FDDR_CORE_RESET_N_net_1;
assign INIT_DONE_net_1         = INIT_DONE_net_0;
assign INIT_DONE               = INIT_DONE_net_1;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------CoreResetP   -   Actel:DirectCore:CoreResetP:7.1.100
CoreResetP #( 
        .DDR_WAIT            ( 200 ),
        .DEVICE_090          ( 0 ),
        .DEVICE_VOLTAGE      ( 2 ),
        .ENABLE_SOFT_RESETS  ( 0 ),
        .EXT_RESET_CFG       ( 0 ),
        .FDDR_IN_USE         ( 1 ),
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
CoreResetP_C0_0(
        // Inputs
        .RESET_N_M2F                    ( RESET_N_M2F ),
        .FIC_2_APB_M_PRESET_N           ( FIC_2_APB_M_PRESET_N ),
        .POWER_ON_RESET_N               ( POWER_ON_RESET_N ),
        .FAB_RESET_N                    ( FAB_RESET_N ),
        .RCOSC_25_50MHZ                 ( RCOSC_25_50MHZ ),
        .CLK_BASE                       ( CLK_BASE ),
        .CLK_LTSSM                      ( GND_net ), // tied to 1'b0 from definition
        .FPLL_LOCK                      ( FPLL_LOCK ),
        .SDIF0_SPLL_LOCK                ( VCC_net ), // tied to 1'b1 from definition
        .SDIF1_SPLL_LOCK                ( VCC_net ), // tied to 1'b1 from definition
        .SDIF2_SPLL_LOCK                ( VCC_net ), // tied to 1'b1 from definition
        .SDIF3_SPLL_LOCK                ( VCC_net ), // tied to 1'b1 from definition
        .CONFIG1_DONE                   ( CONFIG1_DONE ),
        .CONFIG2_DONE                   ( CONFIG2_DONE ),
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
        .MSS_HPMS_READY                 ( MSS_HPMS_READY_net_0 ),
        .DDR_READY                      ( DDR_READY_net_0 ),
        .SDIF_READY                     (  ),
        .RESET_N_F2M                    ( RESET_N_F2M_net_0 ),
        .M3_RESET_N                     ( M3_RESET_N_net_0 ),
        .EXT_RESET_OUT                  (  ),
        .MDDR_DDR_AXI_S_CORE_RESET_N    (  ),
        .FDDR_CORE_RESET_N              ( FDDR_CORE_RESET_N_net_0 ),
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


endmodule
