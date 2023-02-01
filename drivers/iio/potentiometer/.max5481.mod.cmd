cmd_drivers/iio/potentiometer/max5481.mod := printf '%s\n'   max5481.o | awk '!x[$$0]++ { print("drivers/iio/potentiometer/"$$0) }' > drivers/iio/potentiometer/max5481.mod
