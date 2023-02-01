cmd_drivers/iio/accel/msa311.mod := printf '%s\n'   msa311.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/msa311.mod
