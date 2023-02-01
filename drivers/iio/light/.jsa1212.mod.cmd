cmd_drivers/iio/light/jsa1212.mod := printf '%s\n'   jsa1212.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/jsa1212.mod
