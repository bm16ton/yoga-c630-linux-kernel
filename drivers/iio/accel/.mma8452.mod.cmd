cmd_drivers/iio/accel/mma8452.mod := printf '%s\n'   mma8452.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/mma8452.mod
