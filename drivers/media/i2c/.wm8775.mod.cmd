cmd_drivers/media/i2c/wm8775.mod := printf '%s\n'   wm8775.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/wm8775.mod
