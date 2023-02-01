cmd_drivers/iio/adc/ad7091r-base.mod := printf '%s\n'   ad7091r-base.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7091r-base.mod
