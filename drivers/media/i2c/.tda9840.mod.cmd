cmd_drivers/media/i2c/tda9840.mod := printf '%s\n'   tda9840.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tda9840.mod
