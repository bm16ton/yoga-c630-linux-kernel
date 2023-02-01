cmd_drivers/iio/chemical/vz89x.mod := printf '%s\n'   vz89x.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/vz89x.mod
