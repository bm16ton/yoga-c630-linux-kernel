cmd_drivers/iio/adc/ltc2485.mod := printf '%s\n'   ltc2485.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ltc2485.mod
