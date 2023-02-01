cmd_drivers/iio/accel/fxls8962af-spi.mod := printf '%s\n'   fxls8962af-spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/fxls8962af-spi.mod
