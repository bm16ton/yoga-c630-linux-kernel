cmd_drivers/media/i2c/tvp514x.mod := printf '%s\n'   tvp514x.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tvp514x.mod
