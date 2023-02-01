cmd_drivers/i2c/busses/i2c-viperboard.mod := printf '%s\n'   i2c-viperboard.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-viperboard.mod
