cmd_drivers/media/i2c/wm8739.mod := printf '%s\n'   wm8739.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/wm8739.mod
