cmd_drivers/iio/light/isl29018.mod := printf '%s\n'   isl29018.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/isl29018.mod
