cmd_drivers/iio/magnetometer/ak8975.mod := printf '%s\n'   ak8975.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/ak8975.mod
