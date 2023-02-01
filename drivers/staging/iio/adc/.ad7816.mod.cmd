cmd_drivers/staging/iio/adc/ad7816.mod := printf '%s\n'   ad7816.o | awk '!x[$$0]++ { print("drivers/staging/iio/adc/"$$0) }' > drivers/staging/iio/adc/ad7816.mod
