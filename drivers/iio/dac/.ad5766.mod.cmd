cmd_drivers/iio/dac/ad5766.mod := printf '%s\n'   ad5766.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5766.mod
