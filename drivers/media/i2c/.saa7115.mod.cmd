cmd_drivers/media/i2c/saa7115.mod := printf '%s\n'   saa7115.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/saa7115.mod
