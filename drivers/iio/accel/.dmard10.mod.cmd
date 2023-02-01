cmd_drivers/iio/accel/dmard10.mod := printf '%s\n'   dmard10.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/dmard10.mod
