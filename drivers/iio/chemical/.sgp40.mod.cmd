cmd_drivers/iio/chemical/sgp40.mod := printf '%s\n'   sgp40.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/sgp40.mod
