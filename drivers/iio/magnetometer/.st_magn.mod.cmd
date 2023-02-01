cmd_drivers/iio/magnetometer/st_magn.mod := printf '%s\n'   st_magn_core.o st_magn_buffer.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/st_magn.mod
