cmd_drivers/iio/accel/mma7455_core.mod := printf '%s\n'   mma7455_core.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/mma7455_core.mod
