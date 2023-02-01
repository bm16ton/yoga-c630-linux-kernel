cmd_drivers/iio/resolver/ad2s1200.mod := printf '%s\n'   ad2s1200.o | awk '!x[$$0]++ { print("drivers/iio/resolver/"$$0) }' > drivers/iio/resolver/ad2s1200.mod
