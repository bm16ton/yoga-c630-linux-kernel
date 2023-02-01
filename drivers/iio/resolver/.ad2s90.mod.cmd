cmd_drivers/iio/resolver/ad2s90.mod := printf '%s\n'   ad2s90.o | awk '!x[$$0]++ { print("drivers/iio/resolver/"$$0) }' > drivers/iio/resolver/ad2s90.mod
