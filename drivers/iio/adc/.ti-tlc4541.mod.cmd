cmd_drivers/iio/adc/ti-tlc4541.mod := printf '%s\n'   ti-tlc4541.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-tlc4541.mod
