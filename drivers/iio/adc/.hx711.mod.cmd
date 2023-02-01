cmd_drivers/iio/adc/hx711.mod := printf '%s\n'   hx711.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/hx711.mod
