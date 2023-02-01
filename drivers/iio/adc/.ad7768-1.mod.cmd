cmd_drivers/iio/adc/ad7768-1.mod := printf '%s\n'   ad7768-1.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7768-1.mod
