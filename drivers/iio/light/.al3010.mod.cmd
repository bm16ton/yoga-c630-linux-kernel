cmd_drivers/iio/light/al3010.mod := printf '%s\n'   al3010.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/al3010.mod
