set_component MSS_C0_MSS
# Microsemi Corp.
# Date: 2021-May-05 13:21:50
#

create_clock -period 31.25 [ get_pins { MSS_ADLIB_INST/CLK_CONFIG_APB } ]
set_false_path -ignore_errors -through [ get_pins { MSS_ADLIB_INST/CONFIG_PRESET_N } ]
