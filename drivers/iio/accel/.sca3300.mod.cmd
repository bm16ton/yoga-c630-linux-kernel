cmd_drivers/iio/accel/sca3300.mod := printf '%s\n'   sca3300.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/sca3300.mod
