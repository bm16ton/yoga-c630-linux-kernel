cmd_drivers/iio/humidity/hts221_i2c.mod := printf '%s\n'   hts221_i2c.o | awk '!x[$$0]++ { print("drivers/iio/humidity/"$$0) }' > drivers/iio/humidity/hts221_i2c.mod
