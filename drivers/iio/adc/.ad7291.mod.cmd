cmd_drivers/iio/adc/ad7291.mod := printf '%s\n'   ad7291.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7291.mod
