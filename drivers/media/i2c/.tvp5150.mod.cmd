cmd_drivers/media/i2c/tvp5150.mod := printf '%s\n'   tvp5150.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tvp5150.mod
