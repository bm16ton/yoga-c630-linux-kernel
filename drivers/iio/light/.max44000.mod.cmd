cmd_drivers/iio/light/max44000.mod := printf '%s\n'   max44000.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/max44000.mod
