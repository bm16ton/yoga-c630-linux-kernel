cmd_drivers/iio/humidity/am2315.mod := printf '%s\n'   am2315.o | awk '!x[$$0]++ { print("drivers/iio/humidity/"$$0) }' > drivers/iio/humidity/am2315.mod
