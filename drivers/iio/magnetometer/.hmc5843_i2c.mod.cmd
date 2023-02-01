cmd_drivers/iio/magnetometer/hmc5843_i2c.mod := printf '%s\n'   hmc5843_i2c.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/hmc5843_i2c.mod
