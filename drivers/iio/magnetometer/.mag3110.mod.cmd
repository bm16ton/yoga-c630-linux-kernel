cmd_drivers/iio/magnetometer/mag3110.mod := printf '%s\n'   mag3110.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/mag3110.mod
