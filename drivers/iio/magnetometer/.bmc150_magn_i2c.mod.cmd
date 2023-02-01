cmd_drivers/iio/magnetometer/bmc150_magn_i2c.mod := printf '%s\n'   bmc150_magn_i2c.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/bmc150_magn_i2c.mod
