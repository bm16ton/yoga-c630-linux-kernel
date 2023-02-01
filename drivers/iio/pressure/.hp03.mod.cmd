cmd_drivers/iio/pressure/hp03.mod := printf '%s\n'   hp03.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/hp03.mod
