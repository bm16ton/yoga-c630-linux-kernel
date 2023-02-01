cmd_drivers/iio/adc/hi8435.mod := printf '%s\n'   hi8435.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/hi8435.mod
