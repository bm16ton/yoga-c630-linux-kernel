cmd_drivers/iio/magnetometer/st_magn_spi.mod := printf '%s\n'   st_magn_spi.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/st_magn_spi.mod
