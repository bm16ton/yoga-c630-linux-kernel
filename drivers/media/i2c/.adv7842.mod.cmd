cmd_drivers/media/i2c/adv7842.mod := printf '%s\n'   adv7842.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/adv7842.mod
