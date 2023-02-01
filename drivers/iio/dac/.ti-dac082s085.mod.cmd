cmd_drivers/iio/dac/ti-dac082s085.mod := printf '%s\n'   ti-dac082s085.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ti-dac082s085.mod
