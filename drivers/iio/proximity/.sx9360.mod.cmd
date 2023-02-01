cmd_drivers/iio/proximity/sx9360.mod := printf '%s\n'   sx9360.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/sx9360.mod
