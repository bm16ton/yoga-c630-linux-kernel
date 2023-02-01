cmd_drivers/iio/light/isl29028.mod := printf '%s\n'   isl29028.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/isl29028.mod
