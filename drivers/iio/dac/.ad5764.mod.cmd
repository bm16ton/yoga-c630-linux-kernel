cmd_drivers/iio/dac/ad5764.mod := printf '%s\n'   ad5764.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5764.mod
