cmd_drivers/iio/proximity/mb1232.mod := printf '%s\n'   mb1232.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/mb1232.mod
