cmd_drivers/iio/adc/adi-axi-adc.mod := printf '%s\n'   adi-axi-adc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/adi-axi-adc.mod
