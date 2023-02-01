cmd_drivers/iio/imu/bmi160/bmi160_spi.mod := printf '%s\n'   bmi160_spi.o | awk '!x[$$0]++ { print("drivers/iio/imu/bmi160/"$$0) }' > drivers/iio/imu/bmi160/bmi160_spi.mod
