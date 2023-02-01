cmd_drivers/iio/potentiometer/ds1803.mod := printf '%s\n'   ds1803.o | awk '!x[$$0]++ { print("drivers/iio/potentiometer/"$$0) }' > drivers/iio/potentiometer/ds1803.mod
