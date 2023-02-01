cmd_drivers/iio/imu/st_lsm6dsx/st_lsm6dsx_spi.mod := printf '%s\n'   st_lsm6dsx_spi.o | awk '!x[$$0]++ { print("drivers/iio/imu/st_lsm6dsx/"$$0) }' > drivers/iio/imu/st_lsm6dsx/st_lsm6dsx_spi.mod
