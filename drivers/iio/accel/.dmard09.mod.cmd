cmd_drivers/iio/accel/dmard09.mod := printf '%s\n'   dmard09.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/dmard09.mod
