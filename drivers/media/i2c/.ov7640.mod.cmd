cmd_drivers/media/i2c/ov7640.mod := printf '%s\n'   ov7640.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/ov7640.mod
