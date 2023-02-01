cmd_drivers/iio/gyro/adis16260.mod := printf '%s\n'   adis16260.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/adis16260.mod
