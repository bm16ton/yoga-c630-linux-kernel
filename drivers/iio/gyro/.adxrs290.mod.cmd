cmd_drivers/iio/gyro/adxrs290.mod := printf '%s\n'   adxrs290.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/adxrs290.mod
