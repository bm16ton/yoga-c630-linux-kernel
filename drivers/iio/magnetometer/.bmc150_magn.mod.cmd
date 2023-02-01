cmd_drivers/iio/magnetometer/bmc150_magn.mod := printf '%s\n'   bmc150_magn.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/bmc150_magn.mod
