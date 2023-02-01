cmd_drivers/iio/imu/bno055/bno055_i2c.mod := printf '%s\n'   bno055_i2c.o | awk '!x[$$0]++ { print("drivers/iio/imu/bno055/"$$0) }' > drivers/iio/imu/bno055/bno055_i2c.mod
