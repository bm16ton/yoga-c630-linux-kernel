cmd_drivers/iio/adc/dln2-adc.mod := printf '%s\n'   dln2-adc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/dln2-adc.mod
