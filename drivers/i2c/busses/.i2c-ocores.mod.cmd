cmd_drivers/i2c/busses/i2c-ocores.mod := printf '%s\n'   i2c-ocores.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-ocores.mod
