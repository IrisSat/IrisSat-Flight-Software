set_component cdh_tsat5_system_sb_FABOSC_0_OSC
# Microsemi Corp.
# Date: 2019-Apr-18 15:26:43
#

create_clock -ignore_errors -period 20 [ get_pins { I_RCOSC_25_50MHZ/CLKOUT } ]
