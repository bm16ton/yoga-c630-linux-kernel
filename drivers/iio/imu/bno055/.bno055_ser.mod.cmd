cmd_drivers/iio/imu/bno055/bno055_ser.mod := printf '%s\n'   bno055_ser_core.o bno055_ser_trace.o | awk '!x[$$0]++ { print("drivers/iio/imu/bno055/"$$0) }' > drivers/iio/imu/bno055/bno055_ser.mod
