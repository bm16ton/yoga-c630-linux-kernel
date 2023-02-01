cmd_drivers/iio/chemical/scd30_serial.mod := printf '%s\n'   scd30_serial.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/scd30_serial.mod
