cmd_drivers/iio/light/si1133.mod := printf '%s\n'   si1133.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/si1133.mod
