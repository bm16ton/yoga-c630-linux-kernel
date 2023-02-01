cmd_drivers/iio/pressure/st_pressure.mod := printf '%s\n'   st_pressure_core.o st_pressure_buffer.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/st_pressure.mod
