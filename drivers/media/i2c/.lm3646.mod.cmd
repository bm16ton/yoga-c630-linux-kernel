cmd_drivers/media/i2c/lm3646.mod := printf '%s\n'   lm3646.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/lm3646.mod
