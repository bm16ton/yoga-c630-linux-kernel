cmd_drivers/iio/proximity/ping.mod := printf '%s\n'   ping.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/ping.mod
