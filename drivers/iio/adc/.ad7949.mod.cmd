cmd_drivers/iio/adc/ad7949.mod := printf '%s\n'   ad7949.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7949.mod
