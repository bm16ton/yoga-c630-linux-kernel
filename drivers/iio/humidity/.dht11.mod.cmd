cmd_drivers/iio/humidity/dht11.mod := printf '%s\n'   dht11.o | awk '!x[$$0]++ { print("drivers/iio/humidity/"$$0) }' > drivers/iio/humidity/dht11.mod
