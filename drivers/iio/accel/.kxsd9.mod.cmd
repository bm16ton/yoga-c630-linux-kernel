cmd_drivers/iio/accel/kxsd9.mod := printf '%s\n'   kxsd9.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/kxsd9.mod
