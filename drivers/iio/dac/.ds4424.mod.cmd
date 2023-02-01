cmd_drivers/iio/dac/ds4424.mod := printf '%s\n'   ds4424.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ds4424.mod
