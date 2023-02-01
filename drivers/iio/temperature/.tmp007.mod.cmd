cmd_drivers/iio/temperature/tmp007.mod := printf '%s\n'   tmp007.o | awk '!x[$$0]++ { print("drivers/iio/temperature/"$$0) }' > drivers/iio/temperature/tmp007.mod
