cmd_drivers/iio/dac/max5821.mod := printf '%s\n'   max5821.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/max5821.mod
