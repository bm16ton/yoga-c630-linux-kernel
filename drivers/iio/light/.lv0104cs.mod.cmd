cmd_drivers/iio/light/lv0104cs.mod := printf '%s\n'   lv0104cs.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/lv0104cs.mod
