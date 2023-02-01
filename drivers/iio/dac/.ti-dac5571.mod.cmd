cmd_drivers/iio/dac/ti-dac5571.mod := printf '%s\n'   ti-dac5571.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ti-dac5571.mod
