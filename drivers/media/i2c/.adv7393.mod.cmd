cmd_drivers/media/i2c/adv7393.mod := printf '%s\n'   adv7393.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/adv7393.mod
