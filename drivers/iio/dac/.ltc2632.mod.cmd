cmd_drivers/iio/dac/ltc2632.mod := printf '%s\n'   ltc2632.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ltc2632.mod
