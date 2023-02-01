cmd_drivers/iio/dac/ad5446.mod := printf '%s\n'   ad5446.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5446.mod
