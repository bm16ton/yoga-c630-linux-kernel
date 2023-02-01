cmd_drivers/iio/gyro/fxas21002c_core.mod := printf '%s\n'   fxas21002c_core.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/fxas21002c_core.mod
