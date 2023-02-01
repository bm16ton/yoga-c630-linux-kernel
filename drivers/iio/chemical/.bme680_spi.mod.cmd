cmd_drivers/iio/chemical/bme680_spi.mod := printf '%s\n'   bme680_spi.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/bme680_spi.mod
