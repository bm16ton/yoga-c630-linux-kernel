cmd_drivers/iio/proximity/sx9310.mod := printf '%s\n'   sx9310.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/sx9310.mod
