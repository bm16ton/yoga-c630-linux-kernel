cmd_drivers/iio/chemical/scd30_core.mod := printf '%s\n'   scd30_core.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/scd30_core.mod
