cmd_drivers/iio/adc/ti-adc108s102.mod := printf '%s\n'   ti-adc108s102.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ti-adc108s102.mod
