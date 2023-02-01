cmd_drivers/staging/iio/addac/adt7316-i2c.mod := printf '%s\n'   adt7316-i2c.o | awk '!x[$$0]++ { print("drivers/staging/iio/addac/"$$0) }' > drivers/staging/iio/addac/adt7316-i2c.mod
