cmd_drivers/iio/accel/bmi088-accel-core.mod := printf '%s\n'   bmi088-accel-core.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/bmi088-accel-core.mod
