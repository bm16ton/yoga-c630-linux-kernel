cmd_drivers/iio/pressure/bmp280-i2c.mod := printf '%s\n'   bmp280-i2c.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/bmp280-i2c.mod
