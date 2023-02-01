cmd_drivers/media/i2c/cs5345.mod := printf '%s\n'   cs5345.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/cs5345.mod
