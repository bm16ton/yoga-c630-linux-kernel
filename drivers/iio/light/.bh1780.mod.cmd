cmd_drivers/iio/light/bh1780.mod := printf '%s\n'   bh1780.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/bh1780.mod
