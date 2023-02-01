cmd_drivers/iio/pressure/mpl3115.mod := printf '%s\n'   mpl3115.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/mpl3115.mod
