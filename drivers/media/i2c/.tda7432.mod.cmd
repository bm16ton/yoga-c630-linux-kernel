cmd_drivers/media/i2c/tda7432.mod := printf '%s\n'   tda7432.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tda7432.mod
