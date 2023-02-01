cmd_drivers/iio/accel/adxl313_spi.mod := printf '%s\n'   adxl313_spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl313_spi.mod
