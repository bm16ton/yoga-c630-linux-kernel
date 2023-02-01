cmd_drivers/iio/accel/st_accel_i2c.mod := printf '%s\n'   st_accel_i2c.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/st_accel_i2c.mod
