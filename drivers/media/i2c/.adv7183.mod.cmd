cmd_drivers/media/i2c/adv7183.mod := printf '%s\n'   adv7183.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/adv7183.mod
