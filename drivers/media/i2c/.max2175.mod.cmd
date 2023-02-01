cmd_drivers/media/i2c/max2175.mod := printf '%s\n'   max2175.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/max2175.mod
