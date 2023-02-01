cmd_drivers/iio/accel/adxl345_spi.mod := printf '%s\n'   adxl345_spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl345_spi.mod
