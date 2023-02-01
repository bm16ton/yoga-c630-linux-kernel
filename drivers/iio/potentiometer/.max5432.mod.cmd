cmd_drivers/iio/potentiometer/max5432.mod := printf '%s\n'   max5432.o | awk '!x[$$0]++ { print("drivers/iio/potentiometer/"$$0) }' > drivers/iio/potentiometer/max5432.mod
