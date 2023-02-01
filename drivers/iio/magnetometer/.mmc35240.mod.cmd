cmd_drivers/iio/magnetometer/mmc35240.mod := printf '%s\n'   mmc35240.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/mmc35240.mod
