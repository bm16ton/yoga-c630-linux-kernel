cmd_drivers/iio/accel/st_accel_spi.mod := printf '%s\n'   st_accel_spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/st_accel_spi.mod
