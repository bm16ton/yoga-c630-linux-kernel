cmd_drivers/iio/imu/fxos8700_core.mod := printf '%s\n'   fxos8700_core.o | awk '!x[$$0]++ { print("drivers/iio/imu/"$$0) }' > drivers/iio/imu/fxos8700_core.mod
