cmd_drivers/iio/accel/kxsd9-i2c.mod := printf '%s\n'   kxsd9-i2c.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/kxsd9-i2c.mod
