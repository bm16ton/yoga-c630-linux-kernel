cmd_drivers/iio/pressure/ms5611_spi.mod := printf '%s\n'   ms5611_spi.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/ms5611_spi.mod
