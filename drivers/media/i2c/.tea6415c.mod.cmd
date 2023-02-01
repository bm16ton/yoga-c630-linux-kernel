cmd_drivers/media/i2c/tea6415c.mod := printf '%s\n'   tea6415c.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tea6415c.mod
