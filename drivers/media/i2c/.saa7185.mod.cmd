cmd_drivers/media/i2c/saa7185.mod := printf '%s\n'   saa7185.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/saa7185.mod
