cmd_drivers/staging/iio/frequency/ad9832.mod := printf '%s\n'   ad9832.o | awk '!x[$$0]++ { print("drivers/staging/iio/frequency/"$$0) }' > drivers/staging/iio/frequency/ad9832.mod
