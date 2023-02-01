cmd_drivers/iio/pressure/bmp280-spi.mod := printf '%s\n'   bmp280-spi.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/bmp280-spi.mod
