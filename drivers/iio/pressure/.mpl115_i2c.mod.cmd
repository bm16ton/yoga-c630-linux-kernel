cmd_drivers/iio/pressure/mpl115_i2c.mod := printf '%s\n'   mpl115_i2c.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/mpl115_i2c.mod
