cmd_drivers/iio/humidity/hdc100x.mod := printf '%s\n'   hdc100x.o | awk '!x[$$0]++ { print("drivers/iio/humidity/"$$0) }' > drivers/iio/humidity/hdc100x.mod
