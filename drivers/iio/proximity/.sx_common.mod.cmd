cmd_drivers/iio/proximity/sx_common.mod := printf '%s\n'   sx_common.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/sx_common.mod
