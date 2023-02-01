cmd_drivers/iio/accel/fxls8962af-core.mod := printf '%s\n'   fxls8962af-core.o | awk '!x[$$0]++ { print("drivers/iio/accel/"$$0) }' > drivers/iio/accel/fxls8962af-core.mod
