cmd_drivers/iio/imu/fxos8700_spi.mod := printf '%s\n'   fxos8700_spi.o | awk '!x[$$0]++ { print("drivers/iio/imu/"$$0) }' > drivers/iio/imu/fxos8700_spi.mod
