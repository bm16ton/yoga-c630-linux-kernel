cmd_drivers/iio/gyro/adis16080.mod := printf '%s\n'   adis16080.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/adis16080.mod
