cmd_drivers/iio/adc/cc10001_adc.mod := printf '%s\n'   cc10001_adc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/cc10001_adc.mod
