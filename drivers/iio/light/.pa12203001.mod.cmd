cmd_drivers/iio/light/pa12203001.mod := printf '%s\n'   pa12203001.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/pa12203001.mod
