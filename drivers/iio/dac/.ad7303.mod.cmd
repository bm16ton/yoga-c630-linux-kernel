cmd_drivers/iio/dac/ad7303.mod := printf '%s\n'   ad7303.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad7303.mod
