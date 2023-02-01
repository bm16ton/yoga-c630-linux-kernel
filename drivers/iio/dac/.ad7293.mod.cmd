cmd_drivers/iio/dac/ad7293.mod := printf '%s\n'   ad7293.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad7293.mod
