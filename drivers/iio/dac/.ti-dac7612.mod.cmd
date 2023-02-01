cmd_drivers/iio/dac/ti-dac7612.mod := printf '%s\n'   ti-dac7612.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ti-dac7612.mod
