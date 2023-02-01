cmd_drivers/iio/light/apds9300.mod := printf '%s\n'   apds9300.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/apds9300.mod
