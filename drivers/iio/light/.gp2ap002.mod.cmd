cmd_drivers/iio/light/gp2ap002.mod := printf '%s\n'   gp2ap002.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/gp2ap002.mod
