cmd_drivers/iio/gyro/bmg160_spi.mod := printf '%s\n'   bmg160_spi.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/bmg160_spi.mod
