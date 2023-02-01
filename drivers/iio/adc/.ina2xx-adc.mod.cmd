cmd_drivers/iio/adc/ina2xx-adc.mod := printf '%s\n'   ina2xx-adc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ina2xx-adc.mod
