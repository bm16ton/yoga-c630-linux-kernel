cmd_drivers/iio/accel/adxl367_spi.mod := printf '%s\n'   adxl367_spi.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl367_spi.mod
