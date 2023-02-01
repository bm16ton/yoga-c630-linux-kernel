cmd_drivers/iio/cdc/ad7746.mod := printf '%s\n'   ad7746.o | awk '!x[$$0]++ { print("drivers/iio/cdc/"$$0) }' > drivers/iio/cdc/ad7746.mod
