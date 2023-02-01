cmd_drivers/iio/chemical/scd4x.mod := printf '%s\n'   scd4x.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/scd4x.mod
