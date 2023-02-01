cmd_drivers/iio/dac/dpot-dac.mod := printf '%s\n'   dpot-dac.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/dpot-dac.mod
