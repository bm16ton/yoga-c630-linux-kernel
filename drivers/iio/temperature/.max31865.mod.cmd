cmd_drivers/iio/temperature/max31865.mod := printf '%s\n'   max31865.o | awk '!x[$$0]++ { print("drivers/iio/temperature/"$$0) }' > drivers/iio/temperature/max31865.mod
