cmd_drivers/iio/gyro/bmg160_i2c.mod := printf '%s\n'   bmg160_i2c.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/bmg160_i2c.mod
