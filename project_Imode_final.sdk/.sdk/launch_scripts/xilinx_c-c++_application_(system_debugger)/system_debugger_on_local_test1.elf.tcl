connect -url tcp:127.0.0.1:3121
source F:/lynn.zheng/vivado_learing/project_Imode_final/project_Imode_final.sdk/test/ps7_init.tcl
targets -set -filter {name =~"APU" && jtag_cable_name =~ "Digilent Zed 210248686573"} -index 0
loadhw F:/lynn.zheng/vivado_learing/project_Imode_final/project_Imode_final.sdk/test/system.hdf
targets -set -filter {name =~"APU" && jtag_cable_name =~ "Digilent Zed 210248686573"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zed 210248686573"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zed 210248686573"} -index 0
dow F:/lynn.zheng/vivado_learing/project_Imode_final/project_Imode_final.sdk/test1/Debug/test1.elf
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zed 210248686573"} -index 0
con
