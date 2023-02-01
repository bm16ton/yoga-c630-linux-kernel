cmd_drivers/media/i2c/ir-kbd-i2c.mod := printf '%s\n'   ir-kbd-i2c.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/ir-kbd-i2c.mod
