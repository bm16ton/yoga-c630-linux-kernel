cmd_drivers/iio/health/afe4404.mod := printf '%s\n'   afe4404.o | awk '!x[$$0]++ { print("drivers/iio/health/"$$0) }' > drivers/iio/health/afe4404.mod
