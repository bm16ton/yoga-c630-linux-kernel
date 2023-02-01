cmd_drivers/iio/temperature/tsys02d.mod := printf '%s\n'   tsys02d.o | awk '!x[$$0]++ { print("drivers/iio/temperature/"$$0) }' > drivers/iio/temperature/tsys02d.mod
