cmd_drivers/iio/adc/vf610_adc.mod := printf '%s\n'   vf610_adc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/vf610_adc.mod
