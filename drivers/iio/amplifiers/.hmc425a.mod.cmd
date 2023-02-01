cmd_drivers/iio/amplifiers/hmc425a.mod := printf '%s\n'   hmc425a.o | awk '!x[$$0]++ { print("drivers/iio/amplifiers/"$$0) }' > drivers/iio/amplifiers/hmc425a.mod
