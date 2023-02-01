cmd_drivers/iio/imu/adis16480.mod := printf '%s\n'   adis16480.o | awk '!x[$$0]++ { print("drivers/iio/imu/"$$0) }' > drivers/iio/imu/adis16480.mod
