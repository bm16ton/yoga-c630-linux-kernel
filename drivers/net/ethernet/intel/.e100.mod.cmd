cmd_drivers/net/ethernet/intel/e100.mod := printf '%s\n'   e100.o | awk '!x[$$0]++ { print("drivers/net/ethernet/intel/"$$0) }' > drivers/net/ethernet/intel/e100.mod
