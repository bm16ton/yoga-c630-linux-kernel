cmd_drivers/iio/imu/bno055/bno055.mod := printf '%s\n'   bno055.o | awk '!x[$$0]++ { print("drivers/iio/imu/bno055/"$$0) }' > drivers/iio/imu/bno055/bno055.mod
