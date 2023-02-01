cmd_drivers/iio/adc/max11205.mod := printf '%s\n'   max11205.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/max11205.mod
