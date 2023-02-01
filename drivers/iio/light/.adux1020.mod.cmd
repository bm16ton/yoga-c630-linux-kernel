cmd_drivers/iio/light/adux1020.mod := printf '%s\n'   adux1020.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/adux1020.mod
