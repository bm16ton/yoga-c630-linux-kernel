cmd_drivers/iio/light/as73211.mod := printf '%s\n'   as73211.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/as73211.mod
