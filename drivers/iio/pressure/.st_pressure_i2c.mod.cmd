cmd_drivers/iio/pressure/st_pressure_i2c.mod := printf '%s\n'   st_pressure_i2c.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/st_pressure_i2c.mod
