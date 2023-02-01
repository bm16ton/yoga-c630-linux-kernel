cmd_drivers/iio/light/apds9960.mod := printf '%s\n'   apds9960.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/apds9960.mod
