cmd_drivers/staging/fbtft/fbtft.mod := printf '%s\n'   fbtft-core.o fbtft-sysfs.o fbtft-bus.o fbtft-io.o | awk '!x[$$0]++ { print("drivers/staging/fbtft/"$$0) }' > drivers/staging/fbtft/fbtft.mod
