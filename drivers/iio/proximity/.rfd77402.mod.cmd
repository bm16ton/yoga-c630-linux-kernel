cmd_drivers/iio/proximity/rfd77402.mod := printf '%s\n'   rfd77402.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/rfd77402.mod
