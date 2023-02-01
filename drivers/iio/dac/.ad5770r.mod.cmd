cmd_drivers/iio/dac/ad5770r.mod := printf '%s\n'   ad5770r.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5770r.mod
