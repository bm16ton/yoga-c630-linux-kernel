cmd_drivers/media/i2c/sr030pc30.mod := printf '%s\n'   sr030pc30.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/sr030pc30.mod
