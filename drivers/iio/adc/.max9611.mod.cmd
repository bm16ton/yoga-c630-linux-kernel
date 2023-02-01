cmd_drivers/iio/adc/max9611.mod := printf '%s\n'   max9611.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/max9611.mod
