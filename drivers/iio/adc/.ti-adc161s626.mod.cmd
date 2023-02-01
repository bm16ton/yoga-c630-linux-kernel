cmd_drivers/iio/adc/ti-adc161s626.mod := printf '%s\n'   ti-adc161s626.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-adc161s626.mod
