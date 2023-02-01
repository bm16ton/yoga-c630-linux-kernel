cmd_drivers/iio/accel/mma9553.mod := printf '%s\n'   mma9553.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/mma9553.mod
