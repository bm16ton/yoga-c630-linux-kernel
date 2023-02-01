cmd_drivers/iio/accel/sca3000.mod := printf '%s\n'   sca3000.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/sca3000.mod
