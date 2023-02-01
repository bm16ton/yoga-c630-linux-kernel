cmd_drivers/iio/light/tsl4531.mod := printf '%s\n'   tsl4531.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/tsl4531.mod
