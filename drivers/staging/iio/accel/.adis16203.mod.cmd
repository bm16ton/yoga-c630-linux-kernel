cmd_drivers/staging/iio/accel/adis16203.mod := printf '%s\n'   adis16203.o | awk '!x[$$0]++ { print("drivers/staging/iio/accel/"$$0) }' > drivers/staging/iio/accel/adis16203.mod
