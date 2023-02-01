cmd_drivers/iio/pressure/dlhl60d.mod := printf '%s\n'   dlhl60d.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/dlhl60d.mod
