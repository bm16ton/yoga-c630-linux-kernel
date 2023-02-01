cmd_drivers/iio/accel/stk8312.mod := printf '%s\n'   stk8312.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/stk8312.mod
