cmd_drivers/iio/magnetometer/ak8974.mod := printf '%s\n'   ak8974.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/ak8974.mod
