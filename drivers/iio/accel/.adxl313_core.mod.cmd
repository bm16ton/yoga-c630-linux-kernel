cmd_drivers/iio/accel/adxl313_core.mod := printf '%s\n'   adxl313_core.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl313_core.mod
