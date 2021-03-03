//////////////////////////////////////////////////////////////////////
// Created by SmartDesign Fri Feb 26 12:22:56 2021
// Version: v12.6 12.900.20.24
//////////////////////////////////////////////////////////////////////

`timescale 1ns / 100ps

//////////////////////////////////////////////////////////////////////
// Component Description (Tcl) 
//////////////////////////////////////////////////////////////////////
/*
# Exporting Component Description of CoreAPB3_C0 to TCL
# Family: SmartFusion2
# Part Number: M2S010-TQ144
# Create and Configure the core component CoreAPB3_C0
create_and_configure_core -core_vlnv {Actel:DirectCore:CoreAPB3:4.1.100} -component_name {CoreAPB3_C0} -params {\
"APB_DWIDTH:32"  \
"APBSLOT0ENABLE:true"  \
"APBSLOT1ENABLE:true"  \
"APBSLOT2ENABLE:true"  \
"APBSLOT3ENABLE:true"  \
"APBSLOT4ENABLE:true"  \
"APBSLOT5ENABLE:false"  \
"APBSLOT6ENABLE:false"  \
"APBSLOT7ENABLE:false"  \
"APBSLOT8ENABLE:false"  \
"APBSLOT9ENABLE:false"  \
"APBSLOT10ENABLE:false"  \
"APBSLOT11ENABLE:false"  \
"APBSLOT12ENABLE:false"  \
"APBSLOT13ENABLE:false"  \
"APBSLOT14ENABLE:false"  \
"APBSLOT15ENABLE:false"  \
"IADDR_OPTION:0"  \
"MADDR_BITS:20"  \
"SC_0:false"  \
"SC_1:false"  \
"SC_2:false"  \
"SC_3:false"  \
"SC_4:false"  \
"SC_5:false"  \
"SC_6:false"  \
"SC_7:false"  \
"SC_8:false"  \
"SC_9:false"  \
"SC_10:false"  \
"SC_11:false"  \
"SC_12:false"  \
"SC_13:false"  \
"SC_14:false"  \
"SC_15:false"  \
"UPR_NIBBLE_POSN:3"   }
# Exporting Component Description of CoreAPB3_C0 to TCL done
*/

// CoreAPB3_C0
module CoreAPB3_C0(
    // Inputs
    PADDR,
    PENABLE,
    PRDATAS0,
    PRDATAS1,
    PRDATAS2,
    PRDATAS3,
    PRDATAS4,
    PREADYS0,
    PREADYS1,
    PREADYS2,
    PREADYS3,
    PREADYS4,
    PSEL,
    PSLVERRS0,
    PSLVERRS1,
    PSLVERRS2,
    PSLVERRS3,
    PSLVERRS4,
    PWDATA,
    PWRITE,
    // Outputs
    PADDRS,
    PENABLES,
    PRDATA,
    PREADY,
    PSELS0,
    PSELS1,
    PSELS2,
    PSELS3,
    PSELS4,
    PSLVERR,
    PWDATAS,
    PWRITES
);

//--------------------------------------------------------------------
// Input
//--------------------------------------------------------------------
input  [31:0] PADDR;
input         PENABLE;
input  [31:0] PRDATAS0;
input  [31:0] PRDATAS1;
input  [31:0] PRDATAS2;
input  [31:0] PRDATAS3;
input  [31:0] PRDATAS4;
input         PREADYS0;
input         PREADYS1;
input         PREADYS2;
input         PREADYS3;
input         PREADYS4;
input         PSEL;
input         PSLVERRS0;
input         PSLVERRS1;
input         PSLVERRS2;
input         PSLVERRS3;
input         PSLVERRS4;
input  [31:0] PWDATA;
input         PWRITE;
//--------------------------------------------------------------------
// Output
//--------------------------------------------------------------------
output [31:0] PADDRS;
output        PENABLES;
output [31:0] PRDATA;
output        PREADY;
output        PSELS0;
output        PSELS1;
output        PSELS2;
output        PSELS3;
output        PSELS4;
output        PSLVERR;
output [31:0] PWDATAS;
output        PWRITES;
//--------------------------------------------------------------------
// Nets
//--------------------------------------------------------------------
wire   [31:0] PADDR;
wire          PENABLE;
wire   [31:0] APB3mmaster_PRDATA;
wire          APB3mmaster_PREADY;
wire          PSEL;
wire          APB3mmaster_PSLVERR;
wire   [31:0] PWDATA;
wire          PWRITE;
wire   [31:0] APBmslave0_3_PADDR;
wire          APBmslave0_3_PENABLE;
wire   [31:0] PRDATAS0;
wire          PREADYS0;
wire          APBmslave0_3_PSELx;
wire          PSLVERRS0;
wire   [31:0] APBmslave0_3_PWDATA;
wire          APBmslave0_3_PWRITE;
wire   [31:0] PRDATAS1;
wire          PREADYS1;
wire          APBmslave1_3_PSELx;
wire          PSLVERRS1;
wire   [31:0] PRDATAS2;
wire          PREADYS2;
wire          APBmslave2_2_PSELx;
wire          PSLVERRS2;
wire   [31:0] PRDATAS3;
wire          PREADYS3;
wire          APBmslave3_1_PSELx;
wire          PSLVERRS3;
wire   [31:0] PRDATAS4;
wire          PREADYS4;
wire          APBmslave4_0_PSELx;
wire          PSLVERRS4;
wire   [31:0] APB3mmaster_PRDATA_net_0;
wire          APB3mmaster_PREADY_net_0;
wire          APB3mmaster_PSLVERR_net_0;
wire   [31:0] APBmslave0_3_PADDR_net_0;
wire          APBmslave0_3_PSELx_net_0;
wire          APBmslave0_3_PENABLE_net_0;
wire          APBmslave0_3_PWRITE_net_0;
wire   [31:0] APBmslave0_3_PWDATA_net_0;
wire          APBmslave1_3_PSELx_net_0;
wire          APBmslave2_2_PSELx_net_0;
wire          APBmslave3_1_PSELx_net_0;
wire          APBmslave4_0_PSELx_net_0;
//--------------------------------------------------------------------
// TiedOff Nets
//--------------------------------------------------------------------
wire          GND_net;
wire          VCC_net;
wire   [31:0] IADDR_const_net_0;
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
// Constant assignments
//--------------------------------------------------------------------
assign GND_net               = 1'b0;
assign VCC_net               = 1'b1;
assign IADDR_const_net_0     = 32'h00000000;
assign PRDATAS5_const_net_0  = 32'h00000000;
assign PRDATAS6_const_net_0  = 32'h00000000;
assign PRDATAS7_const_net_0  = 32'h00000000;
assign PRDATAS8_const_net_0  = 32'h00000000;
assign PRDATAS9_const_net_0  = 32'h00000000;
assign PRDATAS10_const_net_0 = 32'h00000000;
assign PRDATAS11_const_net_0 = 32'h00000000;
assign PRDATAS12_const_net_0 = 32'h00000000;
assign PRDATAS13_const_net_0 = 32'h00000000;
assign PRDATAS14_const_net_0 = 32'h00000000;
assign PRDATAS15_const_net_0 = 32'h00000000;
assign PRDATAS16_const_net_0 = 32'h00000000;
//--------------------------------------------------------------------
// Top level output port assignments
//--------------------------------------------------------------------
assign APB3mmaster_PRDATA_net_0   = APB3mmaster_PRDATA;
assign PRDATA[31:0]               = APB3mmaster_PRDATA_net_0;
assign APB3mmaster_PREADY_net_0   = APB3mmaster_PREADY;
assign PREADY                     = APB3mmaster_PREADY_net_0;
assign APB3mmaster_PSLVERR_net_0  = APB3mmaster_PSLVERR;
assign PSLVERR                    = APB3mmaster_PSLVERR_net_0;
assign APBmslave0_3_PADDR_net_0   = APBmslave0_3_PADDR;
assign PADDRS[31:0]               = APBmslave0_3_PADDR_net_0;
assign APBmslave0_3_PSELx_net_0   = APBmslave0_3_PSELx;
assign PSELS0                     = APBmslave0_3_PSELx_net_0;
assign APBmslave0_3_PENABLE_net_0 = APBmslave0_3_PENABLE;
assign PENABLES                   = APBmslave0_3_PENABLE_net_0;
assign APBmslave0_3_PWRITE_net_0  = APBmslave0_3_PWRITE;
assign PWRITES                    = APBmslave0_3_PWRITE_net_0;
assign APBmslave0_3_PWDATA_net_0  = APBmslave0_3_PWDATA;
assign PWDATAS[31:0]              = APBmslave0_3_PWDATA_net_0;
assign APBmslave1_3_PSELx_net_0   = APBmslave1_3_PSELx;
assign PSELS1                     = APBmslave1_3_PSELx_net_0;
assign APBmslave2_2_PSELx_net_0   = APBmslave2_2_PSELx;
assign PSELS2                     = APBmslave2_2_PSELx_net_0;
assign APBmslave3_1_PSELx_net_0   = APBmslave3_1_PSELx;
assign PSELS3                     = APBmslave3_1_PSELx_net_0;
assign APBmslave4_0_PSELx_net_0   = APBmslave4_0_PSELx;
assign PSELS4                     = APBmslave4_0_PSELx_net_0;
//--------------------------------------------------------------------
// Component instances
//--------------------------------------------------------------------
//--------CoreAPB3   -   Actel:DirectCore:CoreAPB3:4.1.100
CoreAPB3 #( 
        .APB_DWIDTH      ( 32 ),
        .APBSLOT0ENABLE  ( 1 ),
        .APBSLOT1ENABLE  ( 1 ),
        .APBSLOT2ENABLE  ( 1 ),
        .APBSLOT3ENABLE  ( 1 ),
        .APBSLOT4ENABLE  ( 1 ),
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
CoreAPB3_C0_0(
        // Inputs
        .PRESETN    ( GND_net ), // tied to 1'b0 from definition
        .PCLK       ( GND_net ), // tied to 1'b0 from definition
        .PWRITE     ( PWRITE ),
        .PENABLE    ( PENABLE ),
        .PSEL       ( PSEL ),
        .PREADYS0   ( PREADYS0 ),
        .PSLVERRS0  ( PSLVERRS0 ),
        .PREADYS1   ( PREADYS1 ),
        .PSLVERRS1  ( PSLVERRS1 ),
        .PREADYS2   ( PREADYS2 ),
        .PSLVERRS2  ( PSLVERRS2 ),
        .PREADYS3   ( PREADYS3 ),
        .PSLVERRS3  ( PSLVERRS3 ),
        .PREADYS4   ( PREADYS4 ),
        .PSLVERRS4  ( PSLVERRS4 ),
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
        .PADDR      ( PADDR ),
        .PWDATA     ( PWDATA ),
        .PRDATAS0   ( PRDATAS0 ),
        .PRDATAS1   ( PRDATAS1 ),
        .PRDATAS2   ( PRDATAS2 ),
        .PRDATAS3   ( PRDATAS3 ),
        .PRDATAS4   ( PRDATAS4 ),
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
        .PREADY     ( APB3mmaster_PREADY ),
        .PSLVERR    ( APB3mmaster_PSLVERR ),
        .PWRITES    ( APBmslave0_3_PWRITE ),
        .PENABLES   ( APBmslave0_3_PENABLE ),
        .PSELS0     ( APBmslave0_3_PSELx ),
        .PSELS1     ( APBmslave1_3_PSELx ),
        .PSELS2     ( APBmslave2_2_PSELx ),
        .PSELS3     ( APBmslave3_1_PSELx ),
        .PSELS4     ( APBmslave4_0_PSELx ),
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
        .PRDATA     ( APB3mmaster_PRDATA ),
        .PADDRS     ( APBmslave0_3_PADDR ),
        .PWDATAS    ( APBmslave0_3_PWDATA ) 
        );


endmodule
