cmd_drivers/iio/accel/mma7455_spi.mod := printf '%s\n'   mma7455_spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/mma7455_spi.mod
