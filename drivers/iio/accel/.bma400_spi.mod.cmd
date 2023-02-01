cmd_drivers/iio/accel/bma400_spi.mod := printf '%s\n'   bma400_spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/bma400_spi.mod
