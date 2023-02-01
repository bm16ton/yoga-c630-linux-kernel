cmd_drivers/iio/dac/max517.mod := printf '%s\n'   max517.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/max517.mod
