cmd_drivers/iio/light/stk3310.mod := printf '%s\n'   stk3310.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/stk3310.mod
