cmd_drivers/iio/adc/viperboard_adc.mod := printf '%s\n'   viperboard_adc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/viperboard_adc.mod
