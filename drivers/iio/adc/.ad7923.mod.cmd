cmd_drivers/iio/adc/ad7923.mod := printf '%s\n'   ad7923.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7923.mod
