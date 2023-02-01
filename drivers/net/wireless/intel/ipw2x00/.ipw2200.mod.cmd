cmd_drivers/net/wireless/intel/ipw2x00/ipw2200.mod := printf '%s\n'   ipw2200.o | awk '!x[$$0]++ { print("drivers/net/wireless/intel/ipw2x00/"$$0) }' > drivers/net/wireless/intel/ipw2x00/ipw2200.mod
