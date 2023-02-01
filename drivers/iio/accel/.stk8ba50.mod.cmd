cmd_drivers/iio/accel/stk8ba50.mod := printf '%s\n'   stk8ba50.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/stk8ba50.mod
