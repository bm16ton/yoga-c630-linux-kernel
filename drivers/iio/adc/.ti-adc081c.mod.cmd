cmd_drivers/iio/adc/ti-adc081c.mod := printf '%s\n'   ti-adc081c.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-adc081c.mod
