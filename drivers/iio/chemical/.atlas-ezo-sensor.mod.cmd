cmd_drivers/iio/chemical/atlas-ezo-sensor.mod := printf '%s\n'   atlas-ezo-sensor.o | awk '!x[$$0]++ { print("drivers/iio/chemical/"$$0) }' > drivers/iio/chemical/atlas-ezo-sensor.mod
