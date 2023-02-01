cmd_drivers/iio/pressure/cros_ec_baro.mod := printf '%s\n'   cros_ec_baro.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/cros_ec_baro.mod
