cmd_drivers/iio/accel/kxcjk-1013.mod := printf '%s\n'   kxcjk-1013.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/kxcjk-1013.mod
