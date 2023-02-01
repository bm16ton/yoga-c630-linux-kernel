cmd_drivers/iio/adc/ad7292.mod := printf '%s\n'   ad7292.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7292.mod
