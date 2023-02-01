cmd_drivers/iio/adc/axp20x_adc.mod := printf '%s\n'   axp20x_adc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/axp20x_adc.mod
