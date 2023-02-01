cmd_drivers/iio/imu/inv_mpu6050/inv-mpu6050-spi.mod := printf '%s\n'   inv_mpu_spi.o | awk '!x[$$0]++ { print("drivers/iio/imu/inv_mpu6050/"$$0) }' > drivers/iio/imu/inv_mpu6050/inv-mpu6050-spi.mod
