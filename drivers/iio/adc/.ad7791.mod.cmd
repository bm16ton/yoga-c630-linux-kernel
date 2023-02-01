cmd_drivers/iio/adc/ad7791.mod := printf '%s\n'   ad7791.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7791.mod
