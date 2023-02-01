cmd_drivers/iio/accel/adxl372.mod := printf '%s\n'   adxl372.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl372.mod
