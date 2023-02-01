cmd_drivers/iio/temperature/tsys01.mod := printf '%s\n'   tsys01.o | awk '!x[$$0]++ { print("drivers/iio/temperature/"$$0) }' > drivers/iio/temperature/tsys01.mod
