cmd_drivers/iio/light/tsl2591.mod := printf '%s\n'   tsl2591.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/tsl2591.mod
