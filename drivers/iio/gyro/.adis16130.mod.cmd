cmd_drivers/iio/gyro/adis16130.mod := printf '%s\n'   adis16130.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/adis16130.mod
