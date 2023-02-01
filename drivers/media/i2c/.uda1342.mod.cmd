cmd_drivers/media/i2c/uda1342.mod := printf '%s\n'   uda1342.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/uda1342.mod
