cmd_drivers/iio/dac/ad5696-i2c.mod := printf '%s\n'   ad5696-i2c.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5696-i2c.mod
