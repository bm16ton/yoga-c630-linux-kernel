cmd_drivers/iio/temperature/ltc2983.mod := printf '%s\n'   ltc2983.o | awk '!x[$$0]++ { print("drivers/iio/temperature/"$$0) }' > drivers/iio/temperature/ltc2983.mod
