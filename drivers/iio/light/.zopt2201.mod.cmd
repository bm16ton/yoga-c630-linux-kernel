cmd_drivers/iio/light/zopt2201.mod := printf '%s\n'   zopt2201.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/zopt2201.mod
