cmd_drivers/iio/accel/bmc150-accel-spi.mod := printf '%s\n'   bmc150-accel-spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/bmc150-accel-spi.mod
