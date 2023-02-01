cmd_drivers/media/i2c/saa6588.mod := printf '%s\n'   saa6588.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/saa6588.mod
