cmd_drivers/staging/iio/resolver/ad2s1210.mod := printf '%s\n'   ad2s1210.o | awk '!x[$$0]++ { print("drivers/staging/iio/resolver/"$$0) }' > drivers/staging/iio/resolver/ad2s1210.mod
