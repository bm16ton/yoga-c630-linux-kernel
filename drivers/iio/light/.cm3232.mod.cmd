cmd_drivers/iio/light/cm3232.mod := printf '%s\n'   cm3232.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/cm3232.mod
