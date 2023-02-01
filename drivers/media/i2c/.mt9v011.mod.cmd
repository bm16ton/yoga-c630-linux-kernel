cmd_drivers/media/i2c/mt9v011.mod := printf '%s\n'   mt9v011.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/mt9v011.mod
