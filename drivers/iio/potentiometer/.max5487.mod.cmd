cmd_drivers/iio/potentiometer/max5487.mod := printf '%s\n'   max5487.o | awk '!x[$$0]++ { print("drivers/iio/potentiometer/"$$0) }' > drivers/iio/potentiometer/max5487.mod
