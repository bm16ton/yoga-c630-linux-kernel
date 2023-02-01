cmd_drivers/iio/amplifiers/ad8366.mod := printf '%s\n'   ad8366.o | awk '!x[$$0]++ { print("drivers/iio/amplifiers/"$$0) }' > drivers/iio/amplifiers/ad8366.mod
