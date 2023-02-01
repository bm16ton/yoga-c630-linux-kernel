cmd_drivers/iio/accel/mma9551.mod := printf '%s\n'   mma9551.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/mma9551.mod
