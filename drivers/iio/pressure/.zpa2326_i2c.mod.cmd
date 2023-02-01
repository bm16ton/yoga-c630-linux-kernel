cmd_drivers/iio/pressure/zpa2326_i2c.mod := printf '%s\n'   zpa2326_i2c.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/zpa2326_i2c.mod
