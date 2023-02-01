cmd_drivers/media/i2c/ths8200.mod := printf '%s\n'   ths8200.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/ths8200.mod
