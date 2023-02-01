cmd_drivers/iio/dac/ad5758.mod := printf '%s\n'   ad5758.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5758.mod
