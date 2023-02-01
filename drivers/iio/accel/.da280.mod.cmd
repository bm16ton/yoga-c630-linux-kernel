cmd_drivers/iio/accel/da280.mod := printf '%s\n'   da280.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/da280.mod
