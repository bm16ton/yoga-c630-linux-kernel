cmd_drivers/iio/chemical/ccs811.mod := printf '%s\n'   ccs811.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/ccs811.mod
