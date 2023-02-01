cmd_drivers/iio/adc/ltc2497-core.mod := printf '%s\n'   ltc2497-core.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ltc2497-core.mod
