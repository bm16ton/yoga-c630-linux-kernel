cmd_drivers/iio/adc/ti-adc0832.mod := printf '%s\n'   ti-adc0832.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-adc0832.mod
