//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Wed Jan 16 10:03:01 2019
// Version: v11.9 SP2 11.9.2.1
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// cdh_tsat5_system
module cdh_tsat5_system(
    // Inputs
    DEVRST_N,
    MMUART_0_RXD_F2M,
    // Outputs
    GPIO_0_M2F,
    GPIO_1_M2F,
    GPIO_2_M2F,
    GPIO_3_M2F,
    GPIO_4_M2F,
    GPIO_5_M2F,
    GPIO_6_M2F,
    GPIO_7_M2F,
    MMUART_0_TXD_M2F
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  DEVRST_N;
input  MMUART_0_RXD_F2M;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output GPIO_0_M2F;
output GPIO_1_M2F;
output GPIO_2_M2F;
output GPIO_3_M2F;
output GPIO_4_M2F;
output GPIO_5_M2F;
output GPIO_6_M2F;
output GPIO_7_M2F;
output MMUART_0_TXD_M2F;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   cdh_tsat5_system_sb_0_POWER_ON_RESET_N;
wire   DEVRST_N;
wire   GPIO_0_M2F_net_0;
wire   GPIO_1_M2F_net_0;
wire   GPIO_2_M2F_net_0;
wire   GPIO_3_M2F_net_0;
wire   GPIO_4_M2F_net_0;
wire   GPIO_5_M2F_net_0;
wire   GPIO_6_M2F_net_0;
wire   GPIO_7_M2F_net_0;
wire   MMUART_0_RXD_F2M;
wire   MMUART_0_TXD_M2F_net_0;
wire   MMUART_0_TXD_M2F_net_1;
wire   GPIO_0_M2F_net_1;
wire   GPIO_1_M2F_net_1;
wire   GPIO_2_M2F_net_1;
wire   GPIO_3_M2F_net_1;
wire   GPIO_4_M2F_net_1;
wire   GPIO_5_M2F_net_1;
wire   GPIO_6_M2F_net_1;
wire   GPIO_7_M2F_net_1;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign MMUART_0_TXD_M2F_net_1 = MMUART_0_TXD_M2F_net_0;
assign MMUART_0_TXD_M2F       = MMUART_0_TXD_M2F_net_1;
assign GPIO_0_M2F_net_1       = GPIO_0_M2F_net_0;
assign GPIO_0_M2F             = GPIO_0_M2F_net_1;
assign GPIO_1_M2F_net_1       = GPIO_1_M2F_net_0;
assign GPIO_1_M2F             = GPIO_1_M2F_net_1;
assign GPIO_2_M2F_net_1       = GPIO_2_M2F_net_0;
assign GPIO_2_M2F             = GPIO_2_M2F_net_1;
assign GPIO_3_M2F_net_1       = GPIO_3_M2F_net_0;
assign GPIO_3_M2F             = GPIO_3_M2F_net_1;
assign GPIO_4_M2F_net_1       = GPIO_4_M2F_net_0;
assign GPIO_4_M2F             = GPIO_4_M2F_net_1;
assign GPIO_5_M2F_net_1       = GPIO_5_M2F_net_0;
assign GPIO_5_M2F             = GPIO_5_M2F_net_1;
assign GPIO_6_M2F_net_1       = GPIO_6_M2F_net_0;
assign GPIO_6_M2F             = GPIO_6_M2F_net_1;
assign GPIO_7_M2F_net_1       = GPIO_7_M2F_net_0;
assign GPIO_7_M2F             = GPIO_7_M2F_net_1;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------cdh_tsat5_system_sb
cdh_tsat5_system_sb cdh_tsat5_system_sb_0(
        // Inputs
        .FAB_RESET_N      ( cdh_tsat5_system_sb_0_POWER_ON_RESET_N ),
        .DEVRST_N         ( DEVRST_N ),
        .MMUART_0_RXD_F2M ( MMUART_0_RXD_F2M ),
        // Outputs
        .POWER_ON_RESET_N ( cdh_tsat5_system_sb_0_POWER_ON_RESET_N ),
        .INIT_DONE        (  ),
        .FAB_CCC_GL0      (  ),
        .FAB_CCC_LOCK     (  ),
        .MSS_READY        (  ),
        .MMUART_0_TXD_M2F ( MMUART_0_TXD_M2F_net_0 ),
        .GPIO_0_M2F       ( GPIO_0_M2F_net_0 ),
        .GPIO_1_M2F       ( GPIO_1_M2F_net_0 ),
        .GPIO_2_M2F       ( GPIO_2_M2F_net_0 ),
        .GPIO_3_M2F       ( GPIO_3_M2F_net_0 ),
        .GPIO_4_M2F       ( GPIO_4_M2F_net_0 ),
        .GPIO_5_M2F       ( GPIO_5_M2F_net_0 ),
        .GPIO_6_M2F       ( GPIO_6_M2F_net_0 ),
        .GPIO_7_M2F       ( GPIO_7_M2F_net_0 ) 
        );


endmodule
