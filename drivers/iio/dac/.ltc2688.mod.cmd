cmd_drivers/iio/dac/ltc2688.mod := printf '%s\n'   ltc2688.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ltc2688.mod
