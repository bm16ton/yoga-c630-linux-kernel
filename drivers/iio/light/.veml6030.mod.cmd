cmd_drivers/iio/light/veml6030.mod := printf '%s\n'   veml6030.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/veml6030.mod
