set_family {SmartFusion2}
read_verilog -mode verilog_2k {C:\Work\UMSATS\TSAT5\Libero\cdh-tsat5-libero\component\Actel\DirectCore\CoreResetP\7.1.100\rtl\vlog\core\coreresetp_pcie_hotreset.v}
read_verilog -mode verilog_2k {C:\Work\UMSATS\TSAT5\Libero\cdh-tsat5-libero\component\Actel\DirectCore\CoreResetP\7.1.100\rtl\vlog\core\coreresetp.v}
read_verilog -mode verilog_2k {C:\Work\UMSATS\TSAT5\Libero\cdh-tsat5-libero\component\work\cdh_tsat5_system_sb\CCC_0\cdh_tsat5_system_sb_CCC_0_FCCC.v}
read_verilog -mode verilog_2k {C:\Work\UMSATS\TSAT5\Libero\cdh-tsat5-libero\component\work\cdh_tsat5_system_sb\FABOSC_0\cdh_tsat5_system_sb_FABOSC_0_OSC.v}
read_verilog -mode verilog_2k {C:\Work\UMSATS\TSAT5\Libero\cdh-tsat5-libero\component\work\cdh_tsat5_system_sb_MSS\cdh_tsat5_system_sb_MSS.v}
read_verilog -mode verilog_2k {C:\Work\UMSATS\TSAT5\Libero\cdh-tsat5-libero\component\work\cdh_tsat5_system_sb\cdh_tsat5_system_sb.v}
read_verilog -mode verilog_2k {C:\Work\UMSATS\TSAT5\Libero\cdh-tsat5-libero\component\work\cdh_tsat5_system\cdh_tsat5_system.v}
set_top_level {cdh_tsat5_system}
map_netlist
check_constraints {C:\Work\UMSATS\TSAT5\Libero\cdh-tsat5-libero\constraint\synthesis_sdc_errors.log}
write_fdc {C:\Work\UMSATS\TSAT5\Libero\cdh-tsat5-libero\designer\cdh_tsat5_system\synthesis.fdc}
