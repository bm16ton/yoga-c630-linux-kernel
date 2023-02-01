cmd_drivers/i2c/busses/i2c-xlp9xx.mod := printf '%s\n'   i2c-xlp9xx.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-xlp9xx.mod
