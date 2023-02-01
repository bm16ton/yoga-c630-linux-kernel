cmd_drivers/iio/dac/ad5504.mod := printf '%s\n'   ad5504.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5504.mod
