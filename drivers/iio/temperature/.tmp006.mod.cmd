cmd_drivers/iio/temperature/tmp006.mod := printf '%s\n'   tmp006.o | awk '!x[$$0]++ { print("drivers/iio/temperature/"$$0) }' > drivers/iio/temperature/tmp006.mod
