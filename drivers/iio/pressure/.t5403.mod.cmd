cmd_drivers/iio/pressure/t5403.mod := printf '%s\n'   t5403.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/t5403.mod
