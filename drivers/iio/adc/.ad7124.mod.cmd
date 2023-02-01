cmd_drivers/iio/adc/ad7124.mod := printf '%s\n'   ad7124.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7124.mod
