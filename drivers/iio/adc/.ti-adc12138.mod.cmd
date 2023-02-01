cmd_drivers/iio/adc/ti-adc12138.mod := printf '%s\n'   ti-adc12138.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-adc12138.mod
