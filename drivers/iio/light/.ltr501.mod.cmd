cmd_drivers/iio/light/ltr501.mod := printf '%s\n'   ltr501.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/ltr501.mod
