cmd_drivers/media/i2c/cs3308.mod := printf '%s\n'   cs3308.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/cs3308.mod
