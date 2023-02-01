cmd_drivers/media/i2c/tvaudio.mod := printf '%s\n'   tvaudio.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tvaudio.mod
