cmd_drivers/iio/afe/iio-rescale.mod := printf '%s\n'   iio-rescale.o | awk '!x[$$0]++ { print("drivers/iio/afe/"$$0) }' > drivers/iio/afe/iio-rescale.mod
