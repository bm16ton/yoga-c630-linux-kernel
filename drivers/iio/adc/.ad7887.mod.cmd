cmd_drivers/iio/adc/ad7887.mod := printf '%s\n'   ad7887.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7887.mod
