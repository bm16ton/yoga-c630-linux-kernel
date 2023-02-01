cmd_drivers/iio/adc/max1027.mod := printf '%s\n'   max1027.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/max1027.mod
