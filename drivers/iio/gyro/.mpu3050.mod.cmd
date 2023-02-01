cmd_drivers/iio/gyro/mpu3050.mod := printf '%s\n'   mpu3050-core.o mpu3050-i2c.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/mpu3050.mod
