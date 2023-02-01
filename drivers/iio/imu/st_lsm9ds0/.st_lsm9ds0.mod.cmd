cmd_drivers/iio/imu/st_lsm9ds0/st_lsm9ds0.mod := printf '%s\n'   st_lsm9ds0_core.o | awk '!x[$$0]++ { print("drivers/iio/imu/st_lsm9ds0/"$$0) }' > drivers/iio/imu/st_lsm9ds0/st_lsm9ds0.mod
