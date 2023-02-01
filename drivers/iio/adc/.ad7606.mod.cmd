cmd_drivers/iio/adc/ad7606.mod := printf '%s\n'   ad7606.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7606.mod
