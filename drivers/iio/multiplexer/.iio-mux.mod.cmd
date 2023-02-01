cmd_drivers/iio/multiplexer/iio-mux.mod := printf '%s\n'   iio-mux.o | awk '!x[$$0]++ { print("drivers/iio/multiplexer/"$$0) }' > drivers/iio/multiplexer/iio-mux.mod
