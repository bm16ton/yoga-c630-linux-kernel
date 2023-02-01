cmd_drivers/i2c/busses/i2c-taos-evm.mod := printf '%s\n'   i2c-taos-evm.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-taos-evm.mod
