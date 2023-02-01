cmd_drivers/iio/dac/ad5686.mod := printf '%s\n'   ad5686.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5686.mod
