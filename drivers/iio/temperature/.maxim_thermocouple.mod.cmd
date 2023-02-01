cmd_drivers/iio/temperature/maxim_thermocouple.mod := printf '%s\n'   maxim_thermocouple.o | awk '!x[$$0]++ { print("drivers/iio/temperature/"$$0) }' > drivers/iio/temperature/maxim_thermocouple.mod
