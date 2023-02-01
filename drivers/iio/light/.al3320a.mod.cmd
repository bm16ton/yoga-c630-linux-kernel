cmd_drivers/iio/light/al3320a.mod := printf '%s\n'   al3320a.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/al3320a.mod
