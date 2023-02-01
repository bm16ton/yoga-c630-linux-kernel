cmd_drivers/iio/dac/vf610_dac.mod := printf '%s\n'   vf610_dac.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/vf610_dac.mod
