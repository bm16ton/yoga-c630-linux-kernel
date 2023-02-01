cmd_drivers/iio/accel/da311.mod := printf '%s\n'   da311.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/da311.mod
