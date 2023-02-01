cmd_drivers/media/i2c/ak881x.mod := printf '%s\n'   ak881x.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/ak881x.mod
