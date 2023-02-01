cmd_drivers/iio/imu/adis16400.mod := printf '%s\n'   adis16400.o | awk '!x[$$0]++ { print("drivers/iio/imu/"$$0) }' > drivers/iio/imu/adis16400.mod
