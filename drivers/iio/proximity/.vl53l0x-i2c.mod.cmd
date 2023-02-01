cmd_drivers/iio/proximity/vl53l0x-i2c.mod := printf '%s\n'   vl53l0x-i2c.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/vl53l0x-i2c.mod
