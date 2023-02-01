cmd_drivers/iio/chemical/sps30_i2c.mod := printf '%s\n'   sps30_i2c.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/sps30_i2c.mod
