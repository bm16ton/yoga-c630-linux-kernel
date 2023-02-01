cmd_drivers/iio/accel/adxl313_i2c.mod := printf '%s\n'   adxl313_i2c.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl313_i2c.mod
