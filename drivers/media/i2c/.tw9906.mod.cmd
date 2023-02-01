cmd_drivers/media/i2c/tw9906.mod := printf '%s\n'   tw9906.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tw9906.mod
