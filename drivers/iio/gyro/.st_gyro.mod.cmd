cmd_drivers/iio/gyro/st_gyro.mod := printf '%s\n'   st_gyro_core.o st_gyro_buffer.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/st_gyro.mod
