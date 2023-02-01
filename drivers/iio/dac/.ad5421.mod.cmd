cmd_drivers/iio/dac/ad5421.mod := printf '%s\n'   ad5421.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5421.mod
