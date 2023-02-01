cmd_drivers/iio/accel/bma400_core.mod := printf '%s\n'   bma400_core.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/bma400_core.mod
