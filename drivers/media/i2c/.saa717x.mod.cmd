cmd_drivers/media/i2c/saa717x.mod := printf '%s\n'   saa717x.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/saa717x.mod
