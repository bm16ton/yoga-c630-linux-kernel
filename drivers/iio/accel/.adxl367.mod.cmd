cmd_drivers/iio/accel/adxl367.mod := printf '%s\n'   adxl367.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/adxl367.mod
