cmd_drivers/iio/light/gp2ap020a00f.mod := printf '%s\n'   gp2ap020a00f.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/gp2ap020a00f.mod
