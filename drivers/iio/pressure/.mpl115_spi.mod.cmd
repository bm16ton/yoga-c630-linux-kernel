cmd_drivers/iio/pressure/mpl115_spi.mod := printf '%s\n'   mpl115_spi.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/mpl115_spi.mod
