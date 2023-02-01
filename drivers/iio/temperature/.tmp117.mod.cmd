cmd_drivers/iio/temperature/tmp117.mod := printf '%s\n'   tmp117.o | awk '!x[$$0]++ { print("drivers/iio/temperature/"$$0) }' > drivers/iio/temperature/tmp117.mod
