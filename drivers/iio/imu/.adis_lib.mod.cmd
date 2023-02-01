cmd_drivers/iio/imu/adis_lib.mod := printf '%s\n'   adis.o adis_trigger.o adis_buffer.o | awk '!x[$$0]++ { print("drivers/iio/imu/"$$0) }' > drivers/iio/imu/adis_lib.mod
