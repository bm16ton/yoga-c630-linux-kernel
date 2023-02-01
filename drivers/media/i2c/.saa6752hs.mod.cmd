cmd_drivers/media/i2c/saa6752hs.mod := printf '%s\n'   saa6752hs.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/saa6752hs.mod
