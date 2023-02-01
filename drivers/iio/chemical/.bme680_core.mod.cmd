cmd_drivers/iio/chemical/bme680_core.mod := printf '%s\n'   bme680_core.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/bme680_core.mod
