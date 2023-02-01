cmd_drivers/iio/light/isl29125.mod := printf '%s\n'   isl29125.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/isl29125.mod
