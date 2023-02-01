cmd_drivers/iio/imu/adis16475.mod := printf '%s\n'   adis16475.o | awk '!x[$$0]++ { print("drivers/iio/imu/"$$0) }' > drivers/iio/imu/adis16475.mod
