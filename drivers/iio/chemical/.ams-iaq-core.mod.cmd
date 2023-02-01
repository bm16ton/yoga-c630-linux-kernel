cmd_drivers/iio/chemical/ams-iaq-core.mod := printf '%s\n'   ams-iaq-core.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/ams-iaq-core.mod
