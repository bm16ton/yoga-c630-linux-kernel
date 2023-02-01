cmd_drivers/media/i2c/ad9389b.mod := printf '%s\n'   ad9389b.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/ad9389b.mod
