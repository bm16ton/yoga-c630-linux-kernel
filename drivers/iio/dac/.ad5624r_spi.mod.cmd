cmd_drivers/iio/dac/ad5624r_spi.mod := printf '%s\n'   ad5624r_spi.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5624r_spi.mod
