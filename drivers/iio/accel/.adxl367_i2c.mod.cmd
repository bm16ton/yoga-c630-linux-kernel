cmd_drivers/iio/accel/adxl367_i2c.mod := printf '%s\n'   adxl367_i2c.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl367_i2c.mod
