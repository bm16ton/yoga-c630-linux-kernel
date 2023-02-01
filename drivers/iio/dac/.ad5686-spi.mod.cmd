cmd_drivers/iio/dac/ad5686-spi.mod := printf '%s\n'   ad5686-spi.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5686-spi.mod
