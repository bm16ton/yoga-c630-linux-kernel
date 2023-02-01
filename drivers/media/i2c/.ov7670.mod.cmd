cmd_drivers/media/i2c/ov7670.mod := printf '%s\n'   ov7670.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/ov7670.mod
