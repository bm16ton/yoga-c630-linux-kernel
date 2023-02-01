cmd_drivers/iio/light/veml6070.mod := printf '%s\n'   veml6070.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/veml6070.mod
