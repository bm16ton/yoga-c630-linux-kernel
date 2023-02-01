cmd_drivers/iio/light/tsl2772.mod := printf '%s\n'   tsl2772.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/tsl2772.mod
