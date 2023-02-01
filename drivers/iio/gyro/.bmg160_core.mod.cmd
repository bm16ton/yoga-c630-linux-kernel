cmd_drivers/iio/gyro/bmg160_core.mod := printf '%s\n'   bmg160_core.o | awk '!x[$$0]++ { print("drivers/iio/gyro/"$$0) }' > drivers/iio/gyro/bmg160_core.mod
