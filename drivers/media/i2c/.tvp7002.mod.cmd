cmd_drivers/media/i2c/tvp7002.mod := printf '%s\n'   tvp7002.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tvp7002.mod
