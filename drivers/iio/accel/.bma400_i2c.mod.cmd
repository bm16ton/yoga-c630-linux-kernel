cmd_drivers/iio/accel/bma400_i2c.mod := printf '%s\n'   bma400_i2c.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/bma400_i2c.mod
