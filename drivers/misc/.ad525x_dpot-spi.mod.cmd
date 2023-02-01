cmd_drivers/misc/ad525x_dpot-spi.mod := printf '%s\n'   ad525x_dpot-spi.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/ad525x_dpot-spi.mod
