cmd_drivers/iio/proximity/srf08.mod := printf '%s\n'   srf08.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/srf08.mod
