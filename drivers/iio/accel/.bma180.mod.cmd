cmd_drivers/iio/accel/bma180.mod := printf '%s\n'   bma180.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/bma180.mod
