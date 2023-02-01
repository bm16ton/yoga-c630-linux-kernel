cmd_drivers/iio/proximity/srf04.mod := printf '%s\n'   srf04.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/srf04.mod
