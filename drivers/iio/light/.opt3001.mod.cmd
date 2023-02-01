cmd_drivers/iio/light/opt3001.mod := printf '%s\n'   opt3001.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/opt3001.mod
