cmd_drivers/iio/humidity/htu21.mod := printf '%s\n'   htu21.o | awk '!x[$$0]++ { print("drivers/iio/humidity/"$$0) }' > drivers/iio/humidity/htu21.mod
