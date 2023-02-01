cmd_drivers/iio/dac/ad5791.mod := printf '%s\n'   ad5791.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5791.mod
