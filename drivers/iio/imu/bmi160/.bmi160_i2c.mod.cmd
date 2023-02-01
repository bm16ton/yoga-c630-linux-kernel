cmd_drivers/iio/imu/bmi160/bmi160_i2c.mod := printf '%s\n'   bmi160_i2c.o | awk '!x[$$0]++ { print("drivers/iio/imu/bmi160/"$$0) }' > drivers/iio/imu/bmi160/bmi160_i2c.mod
