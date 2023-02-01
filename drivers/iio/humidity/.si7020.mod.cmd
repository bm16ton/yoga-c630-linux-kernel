cmd_drivers/iio/humidity/si7020.mod := printf '%s\n'   si7020.o | awk '!x[$$0]++ { print("drivers/iio/humidity/"$$0) }' > drivers/iio/humidity/si7020.mod
