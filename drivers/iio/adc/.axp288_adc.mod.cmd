cmd_drivers/iio/adc/axp288_adc.mod := printf '%s\n'   axp288_adc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/axp288_adc.mod
