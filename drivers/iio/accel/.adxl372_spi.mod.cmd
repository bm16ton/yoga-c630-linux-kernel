cmd_drivers/iio/accel/adxl372_spi.mod := printf '%s\n'   adxl372_spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl372_spi.mod
