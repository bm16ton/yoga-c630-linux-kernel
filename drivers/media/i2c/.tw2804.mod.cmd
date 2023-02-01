cmd_drivers/media/i2c/tw2804.mod := printf '%s\n'   tw2804.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tw2804.mod
