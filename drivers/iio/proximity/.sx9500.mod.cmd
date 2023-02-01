cmd_drivers/iio/proximity/sx9500.mod := printf '%s\n'   sx9500.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/sx9500.mod
