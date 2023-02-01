cmd_drivers/iio/chemical/pms7003.mod := printf '%s\n'   pms7003.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/pms7003.mod
