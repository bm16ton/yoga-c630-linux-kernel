cmd_drivers/iio/gyro/adis16136.mod := printf '%s\n'   adis16136.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/adis16136.mod
