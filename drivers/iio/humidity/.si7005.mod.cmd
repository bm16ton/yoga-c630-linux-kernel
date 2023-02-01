cmd_drivers/iio/humidity/si7005.mod := printf '%s\n'   si7005.o | awk '!x[$$0]++ { print("drivers/iio/humidity/"$$0) }' > drivers/iio/humidity/si7005.mod
