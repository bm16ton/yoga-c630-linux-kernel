cmd_drivers/iio/adc/ti-ads8688.mod := printf '%s\n'   ti-ads8688.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-ads8688.mod
