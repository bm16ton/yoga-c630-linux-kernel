cmd_drivers/iio/accel/dmard06.mod := printf '%s\n'   dmard06.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/dmard06.mod
