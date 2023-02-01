cmd_drivers/iio/proximity/as3935.mod := printf '%s\n'   as3935.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/as3935.mod
