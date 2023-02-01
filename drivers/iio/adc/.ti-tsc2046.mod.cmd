cmd_drivers/iio/adc/ti-tsc2046.mod := printf '%s\n'   ti-tsc2046.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-tsc2046.mod
