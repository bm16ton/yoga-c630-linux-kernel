cmd_drivers/i2c/algos/i2c-algo-bit.mod := printf '%s\n'   i2c-algo-bit.o | awk '!x[$$0]++ { print("drivers/i2c/algos/"$$0) }' > drivers/i2c/algos/i2c-algo-bit.mod
