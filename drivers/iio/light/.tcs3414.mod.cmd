cmd_drivers/iio/light/tcs3414.mod := printf '%s\n'   tcs3414.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/tcs3414.mod
