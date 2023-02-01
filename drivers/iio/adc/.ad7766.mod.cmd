cmd_drivers/iio/adc/ad7766.mod := printf '%s\n'   ad7766.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7766.mod
