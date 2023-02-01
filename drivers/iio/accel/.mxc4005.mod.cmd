cmd_drivers/iio/accel/mxc4005.mod := printf '%s\n'   mxc4005.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/mxc4005.mod
