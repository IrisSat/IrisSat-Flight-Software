set_component cdh_tsat5_system_sb_CCC_0_FCCC
# Microsemi Corp.
# Date: 2019-Mar-28 10:46:32
#

create_clock -period 20 [ get_pins { CCC_INST/RCOSC_25_50MHZ } ]
create_generated_clock -multiply_by 64 -divide_by 25 -source [ get_pins { CCC_INST/RCOSC_25_50MHZ } ] -phase 0 [ get_pins { CCC_INST/GL0 } ]
