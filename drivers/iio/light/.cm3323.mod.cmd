cmd_drivers/iio/light/cm3323.mod := printf '%s\n'   cm3323.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/cm3323.mod
