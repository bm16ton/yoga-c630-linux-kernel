cmd_drivers/iio/accel/adxl355_core.mod := printf '%s\n'   adxl355_core.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl355_core.mod
