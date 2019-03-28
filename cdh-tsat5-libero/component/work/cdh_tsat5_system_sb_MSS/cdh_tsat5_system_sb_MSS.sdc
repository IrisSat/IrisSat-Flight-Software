set_component cdh_tsat5_system_sb_MSS
# Microsemi Corp.
# Date: 2019-Mar-28 10:46:28
#

create_clock -period 31.25 [ get_pins { MSS_ADLIB_INST/CLK_CONFIG_APB } ]
set_false_path -ignore_errors -through [ get_pins { MSS_ADLIB_INST/CONFIG_PRESET_N } ]
