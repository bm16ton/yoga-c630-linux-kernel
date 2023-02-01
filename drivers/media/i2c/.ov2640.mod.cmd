cmd_drivers/media/i2c/ov2640.mod := printf '%s\n'   ov2640.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/ov2640.mod
