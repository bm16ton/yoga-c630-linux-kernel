cmd_drivers/iio/accel/kxsd9-spi.mod := printf '%s\n'   kxsd9-spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/kxsd9-spi.mod
