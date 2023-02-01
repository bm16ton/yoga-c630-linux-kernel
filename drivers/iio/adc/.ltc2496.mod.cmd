cmd_drivers/iio/adc/ltc2496.mod := printf '%s\n'   ltc2496.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ltc2496.mod
