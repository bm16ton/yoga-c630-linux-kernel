cmd_drivers/iio/adc/ti-ads8344.mod := printf '%s\n'   ti-ads8344.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-ads8344.mod
