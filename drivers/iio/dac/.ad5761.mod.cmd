cmd_drivers/iio/dac/ad5761.mod := printf '%s\n'   ad5761.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5761.mod
