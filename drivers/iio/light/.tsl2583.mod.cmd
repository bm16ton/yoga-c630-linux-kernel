cmd_drivers/iio/light/tsl2583.mod := printf '%s\n'   tsl2583.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/tsl2583.mod
