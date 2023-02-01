cmd_drivers/iio/dac/ltc1660.mod := printf '%s\n'   ltc1660.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ltc1660.mod
