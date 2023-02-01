cmd_drivers/iio/accel/adis16201.mod := printf '%s\n'   adis16201.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adis16201.mod
