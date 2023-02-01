cmd_drivers/staging/iio/meter/ade7854-i2c.mod := printf '%s\n'   ade7854-i2c.o | awk '!x[$$0]++ { print("drivers/staging/iio/meter/"$$0) }' > drivers/staging/iio/meter/ade7854-i2c.mod
