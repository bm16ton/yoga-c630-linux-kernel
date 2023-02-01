cmd_drivers/fpga/fpga-mgr.mod := printf '%s\n'   fpga-mgr.o | awk '!x[$$0]++ { print("drivers/fpga/"$$0) }' > drivers/fpga/fpga-mgr.mod
