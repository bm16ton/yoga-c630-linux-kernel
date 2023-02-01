cmd_drivers/media/i2c/adv7170.mod := printf '%s\n'   adv7170.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/adv7170.mod
