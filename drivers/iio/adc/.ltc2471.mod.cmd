cmd_drivers/iio/adc/ltc2471.mod := printf '%s\n'   ltc2471.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ltc2471.mod
