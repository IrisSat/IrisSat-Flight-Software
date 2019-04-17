//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Tue Apr 16 14:17:08 2019
// Version: v11.9 SP2 11.9.2.1
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

// cdh_tsat5_system
module cdh_tsat5_system(
    // Inputs
    CAN_RX_F2M,
    DEVRST_N,
    MMUART_0_RXD_F2M,
    m_miso,
    // Outputs
    CAN_TX_M2F,
    GPIO_0_M2F,
    GPIO_1_M2F,
    GPIO_3_M2F,
    GPIO_5_M2F,
    GPIO_6_M2F,
    GPIO_7_M2F,
    MMUART_0_TXD_M2F,
    m_mosi,
    m_sck,
    m_ss
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input        CAN_RX_F2M;
input        DEVRST_N;
input        MMUART_0_RXD_F2M;
input        m_miso;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output       CAN_TX_M2F;
output       GPIO_0_M2F;
output       GPIO_1_M2F;
output       GPIO_3_M2F;
output       GPIO_5_M2F;
output       GPIO_6_M2F;
output       GPIO_7_M2F;
output       MMUART_0_TXD_M2F;
output       m_mosi;
output       m_sck;
output [7:0] m_ss;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire         CAN_RX_F2M;
wire         CAN_TX_M2F_net_0;
wire         cdh_tsat5_system_sb_0_POWER_ON_RESET_N;
wire         DEVRST_N;
wire         GPIO_0_M2F_net_0;
wire         GPIO_1_M2F_net_0;
wire         GPIO_3_M2F_net_0;
wire         GPIO_5_M2F_net_0;
wire         GPIO_6_M2F_net_0;
wire         GPIO_7_M2F_net_0;
wire         m_miso;
wire         m_mosi_net_0;
wire         m_sck_net_0;
wire   [7:0] m_ss_net_0;
wire         MMUART_0_RXD_F2M;
wire         MMUART_0_TXD_M2F_net_0;
wire         MMUART_0_TXD_M2F_net_1;
wire         GPIO_0_M2F_net_1;
wire         GPIO_1_M2F_net_1;
wire         GPIO_3_M2F_net_1;
wire         GPIO_5_M2F_net_1;
wire         GPIO_6_M2F_net_1;
wire         GPIO_7_M2F_net_1;
wire         m_mosi_net_1;
wire         m_sck_net_1;
wire         CAN_TX_M2F_net_1;
wire   [7:0] m_ss_net_1;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire         VCC_net;
//--------------------------------------------------------------------
// Constant assignments
//--------------------------------------------------------------------
assign VCC_net = 1'b1;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
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
assign m_mosi_net_1           = m_mosi_net_0;
assign m_mosi                 = m_mosi_net_1;
assign m_sck_net_1            = m_sck_net_0;
assign m_sck                  = m_sck_net_1;
assign CAN_TX_M2F_net_1       = CAN_TX_M2F_net_0;
assign CAN_TX_M2F             = CAN_TX_M2F_net_1;
assign m_ss_net_1             = m_ss_net_0;
assign m_ss[7:0]              = m_ss_net_1;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------cdh_tsat5_system_sb
cdh_tsat5_system_sb cdh_tsat5_system_sb_0(
        // Inputs
        .FAB_RESET_N      ( cdh_tsat5_system_sb_0_POWER_ON_RESET_N ),
        .DEVRST_N         ( DEVRST_N ),
        .MMUART_0_RXD_F2M ( MMUART_0_RXD_F2M ),
        .CAN_RX_F2M       ( CAN_RX_F2M ),
        .m_miso           ( m_miso ),
        .s_mosi           ( VCC_net ),
        .s_sck            ( VCC_net ),
        .s_ss             ( VCC_net ),
        // Outputs
        .POWER_ON_RESET_N ( cdh_tsat5_system_sb_0_POWER_ON_RESET_N ),
        .INIT_DONE        (  ),
        .FAB_CCC_GL0      (  ),
        .FAB_CCC_LOCK     (  ),
        .MSS_READY        (  ),
        .MMUART_0_TXD_M2F ( MMUART_0_TXD_M2F_net_0 ),
        .CAN_TX_M2F       ( CAN_TX_M2F_net_0 ),
        .CAN_TX_EN_N_M2F  (  ),
        .GPIO_0_M2F       ( GPIO_0_M2F_net_0 ),
        .GPIO_1_M2F       ( GPIO_1_M2F_net_0 ),
        .GPIO_3_M2F       ( GPIO_3_M2F_net_0 ),
        .GPIO_5_M2F       ( GPIO_5_M2F_net_0 ),
        .GPIO_6_M2F       ( GPIO_6_M2F_net_0 ),
        .GPIO_7_M2F       ( GPIO_7_M2F_net_0 ),
        .enable_master    (  ),
        .enable_slave     (  ),
        .m_mosi           ( m_mosi_net_0 ),
        .m_sck            ( m_sck_net_0 ),
        .s_miso           (  ),
        .m_ss             ( m_ss_net_0 ) 
        );


endmodule
