cmd_drivers/iio/gyro/itg3200.mod := printf '%s\n'   itg3200_core.o itg3200_buffer.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/itg3200.mod
