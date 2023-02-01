cmd_drivers/iio/light/max44009.mod := printf '%s\n'   max44009.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/max44009.mod
