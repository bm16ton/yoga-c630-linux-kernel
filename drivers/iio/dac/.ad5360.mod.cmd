cmd_drivers/iio/dac/ad5360.mod := printf '%s\n'   ad5360.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5360.mod
