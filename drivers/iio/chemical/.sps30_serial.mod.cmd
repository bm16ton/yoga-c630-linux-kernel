cmd_drivers/iio/chemical/sps30_serial.mod := printf '%s\n'   sps30_serial.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/sps30_serial.mod
