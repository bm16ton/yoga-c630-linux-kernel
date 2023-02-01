cmd_drivers/iio/adc/ti-adc084s021.mod := printf '%s\n'   ti-adc084s021.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-adc084s021.mod
