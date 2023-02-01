cmd_drivers/media/i2c/tea6420.mod := printf '%s\n'   tea6420.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tea6420.mod
