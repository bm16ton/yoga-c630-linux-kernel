cmd_drivers/iio/adc/ad7780.mod := printf '%s\n'   ad7780.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7780.mod
