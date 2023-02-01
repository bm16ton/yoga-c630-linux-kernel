cmd_drivers/iio/chemical/sps30.mod := printf '%s\n'   sps30.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/sps30.mod
