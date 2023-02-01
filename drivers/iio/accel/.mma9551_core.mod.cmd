cmd_drivers/iio/accel/mma9551_core.mod := printf '%s\n'   mma9551_core.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/mma9551_core.mod
