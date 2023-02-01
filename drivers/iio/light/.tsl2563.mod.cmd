cmd_drivers/iio/light/tsl2563.mod := printf '%s\n'   tsl2563.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/tsl2563.mod
