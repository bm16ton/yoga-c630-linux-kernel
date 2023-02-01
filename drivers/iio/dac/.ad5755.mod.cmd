cmd_drivers/iio/dac/ad5755.mod := printf '%s\n'   ad5755.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5755.mod
