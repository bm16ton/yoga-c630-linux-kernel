cmd_drivers/iio/potentiometer/ad5272.mod := printf '%s\n'   ad5272.o | awk '!x[$$0]++ { print("drivers/iio/potentiometer/"$$0) }' > drivers/iio/potentiometer/ad5272.mod
