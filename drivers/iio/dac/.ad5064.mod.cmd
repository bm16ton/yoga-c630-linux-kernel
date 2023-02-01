cmd_drivers/iio/dac/ad5064.mod := printf '%s\n'   ad5064.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5064.mod
