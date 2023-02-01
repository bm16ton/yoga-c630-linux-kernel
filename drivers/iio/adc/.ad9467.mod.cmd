cmd_drivers/iio/adc/ad9467.mod := printf '%s\n'   ad9467.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad9467.mod
