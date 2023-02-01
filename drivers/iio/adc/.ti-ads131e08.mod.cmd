cmd_drivers/iio/adc/ti-ads131e08.mod := printf '%s\n'   ti-ads131e08.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-ads131e08.mod
