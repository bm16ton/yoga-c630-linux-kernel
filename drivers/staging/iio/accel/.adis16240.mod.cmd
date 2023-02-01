cmd_drivers/staging/iio/accel/adis16240.mod := printf '%s\n'   adis16240.o | awk '!x[$$0]++ { print("drivers/staging/iio/accel/"$$0) }' > drivers/staging/iio/accel/adis16240.mod
