cmd_drivers/iio/humidity/hts221_spi.mod := printf '%s\n'   hts221_spi.o | awk '!x[$$0]++ { print("drivers/iio/humidity/"$$0) }' > drivers/iio/humidity/hts221_spi.mod
