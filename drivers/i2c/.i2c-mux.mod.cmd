cmd_drivers/i2c/i2c-mux.mod := printf '%s\n'   i2c-mux.o | awk '!x[$$0]++ { print("drivers/i2c/"$$0) }' > drivers/i2c/i2c-mux.mod
