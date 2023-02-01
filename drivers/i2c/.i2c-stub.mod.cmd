cmd_drivers/i2c/i2c-stub.mod := printf '%s\n'   i2c-stub.o | awk '!x[$$0]++ { print("drivers/i2c/"$$0) }' > drivers/i2c/i2c-stub.mod
