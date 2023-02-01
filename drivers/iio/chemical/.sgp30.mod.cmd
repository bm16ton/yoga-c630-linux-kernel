cmd_drivers/iio/chemical/sgp30.mod := printf '%s\n'   sgp30.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/sgp30.mod
