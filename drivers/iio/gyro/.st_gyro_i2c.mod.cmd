cmd_drivers/iio/gyro/st_gyro_i2c.mod := printf '%s\n'   st_gyro_i2c.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/st_gyro_i2c.mod
