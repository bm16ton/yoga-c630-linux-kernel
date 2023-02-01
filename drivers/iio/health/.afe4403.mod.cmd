cmd_drivers/iio/health/afe4403.mod := printf '%s\n'   afe4403.o | awk '!x[$$0]++ { print("drivers/iio/health/"$$0) }' > drivers/iio/health/afe4403.mod
