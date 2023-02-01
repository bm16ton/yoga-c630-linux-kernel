cmd_drivers/media/i2c/ks0127.mod := printf '%s\n'   ks0127.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/ks0127.mod
