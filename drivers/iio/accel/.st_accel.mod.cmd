cmd_drivers/iio/accel/st_accel.mod := printf '%s\n'   st_accel_core.o st_accel_buffer.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/st_accel.mod
