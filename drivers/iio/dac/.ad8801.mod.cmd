cmd_drivers/iio/dac/ad8801.mod := printf '%s\n'   ad8801.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad8801.mod
