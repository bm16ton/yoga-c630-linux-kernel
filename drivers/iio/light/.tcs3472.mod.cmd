cmd_drivers/iio/light/tcs3472.mod := printf '%s\n'   tcs3472.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/tcs3472.mod
