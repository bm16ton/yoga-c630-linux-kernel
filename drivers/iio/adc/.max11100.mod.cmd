cmd_drivers/iio/adc/max11100.mod := printf '%s\n'   max11100.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/max11100.mod
