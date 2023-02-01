cmd_drivers/misc/ad525x_dpot.mod := printf '%s\n'   ad525x_dpot.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/ad525x_dpot.mod
