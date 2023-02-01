cmd_drivers/iio/accel/bma220_spi.mod := printf '%s\n'   bma220_spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/bma220_spi.mod
