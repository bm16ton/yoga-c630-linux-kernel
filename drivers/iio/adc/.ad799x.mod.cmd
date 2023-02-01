cmd_drivers/iio/adc/ad799x.mod := printf '%s\n'   ad799x.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad799x.mod
