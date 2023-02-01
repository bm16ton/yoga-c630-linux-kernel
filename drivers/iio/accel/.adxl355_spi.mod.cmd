cmd_drivers/iio/accel/adxl355_spi.mod := printf '%s\n'   adxl355_spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl355_spi.mod
