cmd_drivers/iio/health/max30102.mod := printf '%s\n'   max30102.o | awk '!x[$$0]++ { print("drivers/iio/health/"$$0) }' > drivers/iio/health/max30102.mod
