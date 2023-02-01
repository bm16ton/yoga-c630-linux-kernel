cmd_drivers/iio/adc/ti-ads1015.mod := printf '%s\n'   ti-ads1015.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-ads1015.mod
