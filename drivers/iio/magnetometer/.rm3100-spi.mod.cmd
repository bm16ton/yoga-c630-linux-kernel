cmd_drivers/iio/magnetometer/rm3100-spi.mod := printf '%s\n'   rm3100-spi.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/rm3100-spi.mod
