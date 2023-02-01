cmd_drivers/iio/adc/ti-adc128s052.mod := printf '%s\n'   ti-adc128s052.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-adc128s052.mod
