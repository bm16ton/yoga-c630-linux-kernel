cmd_drivers/iio/humidity/hdc2010.mod := printf '%s\n'   hdc2010.o | awk '!x[$$0]++ { print("drivers/iio/humidity/"$$0) }' > drivers/iio/humidity/hdc2010.mod
