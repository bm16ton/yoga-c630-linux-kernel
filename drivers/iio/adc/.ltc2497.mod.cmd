cmd_drivers/iio/adc/ltc2497.mod := printf '%s\n'   ltc2497.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ltc2497.mod
