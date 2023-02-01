cmd_drivers/iio/proximity/sx9324.mod := printf '%s\n'   sx9324.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/sx9324.mod
