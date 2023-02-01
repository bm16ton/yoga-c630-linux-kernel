cmd_drivers/iio/adc/rtq6056.mod := printf '%s\n'   rtq6056.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/rtq6056.mod
