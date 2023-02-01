cmd_drivers/media/i2c/max9286.mod := printf '%s\n'   max9286.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/max9286.mod
