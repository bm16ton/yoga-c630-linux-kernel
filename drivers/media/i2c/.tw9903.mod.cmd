cmd_drivers/media/i2c/tw9903.mod := printf '%s\n'   tw9903.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tw9903.mod
