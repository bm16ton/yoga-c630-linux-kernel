cmd_drivers/media/i2c/cs53l32a.mod := printf '%s\n'   cs53l32a.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/cs53l32a.mod
