cmd_drivers/media/i2c/vpx3220.mod := printf '%s\n'   vpx3220.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/vpx3220.mod
