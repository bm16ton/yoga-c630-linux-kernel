cmd_drivers/iio/pressure/dps310.mod := printf '%s\n'   dps310.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/dps310.mod
