cmd_drivers/iio/pressure/bmp280.mod := printf '%s\n'   bmp280-core.o bmp280-regmap.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/bmp280.mod
