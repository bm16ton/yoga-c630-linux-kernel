cmd_drivers/iio/accel/mc3230.mod := printf '%s\n'   mc3230.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/mc3230.mod
