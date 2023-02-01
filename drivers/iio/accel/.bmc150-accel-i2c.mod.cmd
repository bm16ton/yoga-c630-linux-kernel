cmd_drivers/iio/accel/bmc150-accel-i2c.mod := printf '%s\n'   bmc150-accel-i2c.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/bmc150-accel-i2c.mod
