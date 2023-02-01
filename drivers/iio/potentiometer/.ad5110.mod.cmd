cmd_drivers/iio/potentiometer/ad5110.mod := printf '%s\n'   ad5110.o | awk '!x[$$0]++ { print("drivers/iio/potentiometer/"$$0) }' > drivers/iio/potentiometer/ad5110.mod
