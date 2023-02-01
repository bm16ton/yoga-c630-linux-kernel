cmd_drivers/iio/accel/adxl345_core.mod := printf '%s\n'   adxl345_core.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl345_core.mod
