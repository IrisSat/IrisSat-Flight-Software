set_component cdh_tsat5_system_sb_FABOSC_0_OSC
# Microsemi Corp.
# Date: 2020-Mar-30 00:06:52
#

create_clock -ignore_errors -period 20 [ get_pins { I_RCOSC_25_50MHZ/CLKOUT } ]
