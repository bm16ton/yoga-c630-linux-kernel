cmd_drivers/iio/dac/ad5592r-base.mod := printf '%s\n'   ad5592r-base.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/ad5592r-base.mod
