cmd_drivers/iio/adc/ad7298.mod := printf '%s\n'   ad7298.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7298.mod
