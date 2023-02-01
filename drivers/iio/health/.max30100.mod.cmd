cmd_drivers/iio/health/max30100.mod := printf '%s\n'   max30100.o | awk '!x[$$0]++ { print("drivers/iio/health/"$$0) }' > drivers/iio/health/max30100.mod
