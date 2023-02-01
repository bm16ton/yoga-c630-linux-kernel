cmd_drivers/staging/iio/frequency/ad9834.mod := printf '%s\n'   ad9834.o | awk '!x[$$0]++ { print("drivers/staging/iio/frequency/"$$0) }' > drivers/staging/iio/frequency/ad9834.mod
