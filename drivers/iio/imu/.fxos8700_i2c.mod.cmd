cmd_drivers/iio/imu/fxos8700_i2c.mod := printf '%s\n'   fxos8700_i2c.o | awk '!x[$$0]++ { print("drivers/iio/imu/"$$0) }' > drivers/iio/imu/fxos8700_i2c.mod
