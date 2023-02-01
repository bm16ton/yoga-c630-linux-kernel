cmd_drivers/iio/pressure/ms5637.mod := printf '%s\n'   ms5637.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/ms5637.mod
