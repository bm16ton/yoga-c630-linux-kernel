cmd_drivers/iio/light/cm3605.mod := printf '%s\n'   cm3605.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/cm3605.mod
