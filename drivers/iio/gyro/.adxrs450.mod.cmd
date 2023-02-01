cmd_drivers/iio/gyro/adxrs450.mod := printf '%s\n'   adxrs450.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/adxrs450.mod
