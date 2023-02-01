cmd_drivers/iio/light/si1145.mod := printf '%s\n'   si1145.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/si1145.mod
