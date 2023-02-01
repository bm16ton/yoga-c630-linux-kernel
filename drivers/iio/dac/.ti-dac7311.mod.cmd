cmd_drivers/iio/dac/ti-dac7311.mod := printf '%s\n'   ti-dac7311.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ti-dac7311.mod
