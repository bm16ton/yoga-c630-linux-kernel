cmd_drivers/media/i2c/tc358743.mod := printf '%s\n'   tc358743.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/tc358743.mod
