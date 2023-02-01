cmd_drivers/iio/temperature/max31856.mod := printf '%s\n'   max31856.o | awk '!x[$$0]++ { print("drivers/iio/temperature/"$$0) }' > drivers/iio/temperature/max31856.mod
