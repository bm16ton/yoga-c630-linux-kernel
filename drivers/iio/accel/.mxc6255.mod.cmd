cmd_drivers/iio/accel/mxc6255.mod := printf '%s\n'   mxc6255.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/mxc6255.mod
