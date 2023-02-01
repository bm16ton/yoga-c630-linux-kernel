cmd_drivers/iio/magnetometer/rm3100-core.mod := printf '%s\n'   rm3100-core.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/rm3100-core.mod
