cmd_drivers/media/i2c/tw9910.mod := printf '%s\n'   tw9910.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tw9910.mod
