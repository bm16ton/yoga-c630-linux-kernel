cmd_drivers/iio/adc/max1241.mod := printf '%s\n'   max1241.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/max1241.mod
