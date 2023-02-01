cmd_drivers/iio/potentiometer/tpl0102.mod := printf '%s\n'   tpl0102.o | awk '!x[$$0]++ { print("drivers/iio/potentiometer/"$$0) }' > drivers/iio/potentiometer/tpl0102.mod
