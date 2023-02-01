cmd_drivers/iio/light/vl6180.mod := printf '%s\n'   vl6180.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/vl6180.mod
