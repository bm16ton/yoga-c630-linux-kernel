cmd_drivers/iio/chemical/sunrise_co2.mod := printf '%s\n'   sunrise_co2.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/sunrise_co2.mod
