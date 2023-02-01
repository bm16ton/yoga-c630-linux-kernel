cmd_drivers/iio/cdc/ad7150.mod := printf '%s\n'   ad7150.o | awk '!x[$$0]++ { print("drivers/iio/cdc/"$$0) }' > drivers/iio/cdc/ad7150.mod
