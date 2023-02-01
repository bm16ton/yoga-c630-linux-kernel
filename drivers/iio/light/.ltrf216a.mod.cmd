cmd_drivers/iio/light/ltrf216a.mod := printf '%s\n'   ltrf216a.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/ltrf216a.mod
