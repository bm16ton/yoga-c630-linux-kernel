cmd_drivers/i2c/busses/i2c-thunderx.mod := printf '%s\n'   i2c-octeon-core.o i2c-thunderx-pcidrv.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-thunderx.mod
