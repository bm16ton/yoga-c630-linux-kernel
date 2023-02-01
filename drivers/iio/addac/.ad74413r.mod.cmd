cmd_drivers/iio/addac/ad74413r.mod := printf '%s\n'   ad74413r.o | awk '!x[$$0]++ { print("drivers/iio/addac/"$$0) }' > drivers/iio/addac/ad74413r.mod
