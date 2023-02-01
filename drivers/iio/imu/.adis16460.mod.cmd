cmd_drivers/iio/imu/adis16460.mod := printf '%s\n'   adis16460.o | awk '!x[$$0]++ { print("drivers/iio/imu/"$$0) }' > drivers/iio/imu/adis16460.mod
