cmd_drivers/iio/gyro/st_gyro_spi.mod := printf '%s\n'   st_gyro_spi.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/st_gyro_spi.mod
