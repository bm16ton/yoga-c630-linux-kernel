cmd_drivers/iio/accel/mma7660.mod := printf '%s\n'   mma7660.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/mma7660.mod
