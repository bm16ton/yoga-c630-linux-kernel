cmd_drivers/iio/chemical/bme680_i2c.mod := printf '%s\n'   bme680_i2c.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/bme680_i2c.mod
