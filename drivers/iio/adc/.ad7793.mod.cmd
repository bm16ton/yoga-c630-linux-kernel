cmd_drivers/iio/adc/ad7793.mod := printf '%s\n'   ad7793.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7793.mod
