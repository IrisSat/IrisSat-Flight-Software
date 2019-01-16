# ===========================================================
# Created by Microsemi SmartDesign Wed Jan 16 09:58:42 2019
# 
# Warning: Do not modify this file, it may lead to unexpected 
#          simulation failures in your design.
#
# ===========================================================

if {$tcl_platform(os) == "Linux"} {
  exec "$env(ACTEL_SW_DIR)/bin/bfmtovec" -in test.bfm -out test.vec
} else {
  exec "$env(ACTEL_SW_DIR)/bin/bfmtovec.exe" -in test.bfm -out test.vec
}
