cmd_drivers/iio/adc/max1118.mod := printf '%s\n'   max1118.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/max1118.mod
