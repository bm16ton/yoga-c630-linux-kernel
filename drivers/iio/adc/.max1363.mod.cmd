cmd_drivers/iio/adc/max1363.mod := printf '%s\n'   max1363.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/max1363.mod
