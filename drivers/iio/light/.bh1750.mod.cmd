cmd_drivers/iio/light/bh1750.mod := printf '%s\n'   bh1750.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/bh1750.mod
