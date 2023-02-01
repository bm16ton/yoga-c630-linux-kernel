cmd_drivers/iio/adc/ad7476.mod := printf '%s\n'   ad7476.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7476.mod
