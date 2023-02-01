cmd_drivers/iio/light/cm36651.mod := printf '%s\n'   cm36651.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/cm36651.mod
