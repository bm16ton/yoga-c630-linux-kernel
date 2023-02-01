cmd_drivers/iio/gyro/fxas21002c_i2c.mod := printf '%s\n'   fxas21002c_i2c.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/fxas21002c_i2c.mod
