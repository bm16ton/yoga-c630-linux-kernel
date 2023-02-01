cmd_drivers/media/i2c/ml86v7667.mod := printf '%s\n'   ml86v7667.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/ml86v7667.mod
