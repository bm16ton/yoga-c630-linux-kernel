cmd_drivers/iio/accel/adis16209.mod := printf '%s\n'   adis16209.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adis16209.mod
