cmd_drivers/media/i2c/isl7998x.mod := printf '%s\n'   isl7998x.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/isl7998x.mod
