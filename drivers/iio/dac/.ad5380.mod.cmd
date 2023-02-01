cmd_drivers/iio/dac/ad5380.mod := printf '%s\n'   ad5380.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5380.mod
