cmd_drivers/iio/proximity/isl29501.mod := printf '%s\n'   isl29501.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/isl29501.mod
