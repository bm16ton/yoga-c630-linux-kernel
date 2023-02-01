cmd_drivers/iio/accel/fxls8962af-i2c.mod := printf '%s\n'   fxls8962af-i2c.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/fxls8962af-i2c.mod
