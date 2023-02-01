cmd_drivers/iio/accel/cros_ec_accel_legacy.mod := printf '%s\n'   cros_ec_accel_legacy.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/cros_ec_accel_legacy.mod
