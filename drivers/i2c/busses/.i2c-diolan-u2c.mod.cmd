cmd_drivers/i2c/busses/i2c-diolan-u2c.mod := printf '%s\n'   i2c-diolan-u2c.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-diolan-u2c.mod
