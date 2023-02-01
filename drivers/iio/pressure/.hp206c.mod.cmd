cmd_drivers/iio/pressure/hp206c.mod := printf '%s\n'   hp206c.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/hp206c.mod
