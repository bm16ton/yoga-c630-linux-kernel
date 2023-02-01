cmd_drivers/iio/chemical/scd30_i2c.mod := printf '%s\n'   scd30_i2c.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/scd30_i2c.mod
