cmd_drivers/iio/imu/st_lsm6dsx/st_lsm6dsx_i2c.mod := printf '%s\n'   st_lsm6dsx_i2c.o | awk '!x[$$0]++ { print("drivers/iio/imu/st_lsm6dsx/"$$0) }' > drivers/iio/imu/st_lsm6dsx/st_lsm6dsx_i2c.mod
