cmd_drivers/media/i2c/adp1653.mod := printf '%s\n'   adp1653.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/adp1653.mod
