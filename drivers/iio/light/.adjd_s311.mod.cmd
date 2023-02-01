cmd_drivers/iio/light/adjd_s311.mod := printf '%s\n'   adjd_s311.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/adjd_s311.mod
