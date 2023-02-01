cmd_drivers/iio/light/rpr0521.mod := printf '%s\n'   rpr0521.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/rpr0521.mod
