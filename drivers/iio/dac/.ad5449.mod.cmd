cmd_drivers/iio/dac/ad5449.mod := printf '%s\n'   ad5449.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5449.mod
