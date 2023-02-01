cmd_drivers/iio/dac/m62332.mod := printf '%s\n'   m62332.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/m62332.mod
