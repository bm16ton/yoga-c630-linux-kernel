cmd_drivers/media/i2c/bt856.mod := printf '%s\n'   bt856.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/bt856.mod
