cmd_drivers/iio/light/cros_ec_light_prox.mod := printf '%s\n'   cros_ec_light_prox.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/cros_ec_light_prox.mod
