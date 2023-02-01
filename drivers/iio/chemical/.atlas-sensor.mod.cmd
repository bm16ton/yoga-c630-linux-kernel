cmd_drivers/iio/chemical/atlas-sensor.mod := printf '%s\n'   atlas-sensor.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/atlas-sensor.mod
