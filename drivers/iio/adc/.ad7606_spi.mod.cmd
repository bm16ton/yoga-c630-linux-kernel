cmd_drivers/iio/adc/ad7606_spi.mod := printf '%s\n'   ad7606_spi.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7606_spi.mod
