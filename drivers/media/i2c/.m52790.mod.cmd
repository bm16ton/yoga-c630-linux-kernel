cmd_drivers/media/i2c/m52790.mod := printf '%s\n'   m52790.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/m52790.mod
