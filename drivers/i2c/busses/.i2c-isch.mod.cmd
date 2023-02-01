cmd_drivers/i2c/busses/i2c-isch.mod := printf '%s\n'   i2c-isch.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-isch.mod
